//
// Created by daniil on 5/21/22.
//

#include "RequestHandler.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "../dbController/dbController.h"
#include "../GlobalConfigs/GlobalCOnfigs.h"

#define MAX_REQUEST_SIZE 1500
#define MAX_REQUEST_NUMBER 300

void Login(char* request, ReqAnswer* answer){
    char* usrName, *usrPassword;
    char type[100];
    answer->count = 1;
    usrName = (char*) malloc(sizeof(char)*100);
    usrPassword = (char*) malloc(sizeof(char)*100);
    sscanf(request, "%s %s %s", type, usrName, usrPassword);
    bool res = CheckCorrectUserData_db(usrName, usrPassword);
    char* ans = (char*) malloc(sizeof(char)*100);
    int code;
    if (res == true){
        strcpy(ans, "CODE");
        strcat(ans, " 34901");
    }
    else{
        strcpy(ans, "ERR");
    }
    answer->Answers[0] = ans;
    code_name_globalConfig[list_index_globalConfigs] = usrName;
    code_list_globalConfig[list_index_globalConfigs++] = "34901";
}

void Register(char* request, ReqAnswer* answer){
    //write this fucking code, bro
}

void SendNewMess(char* request, ReqAnswer* answer){
    char type[100];
    char uniq_code[100];
    char* receiver = (char*) malloc(sizeof(char)*100);
    char* message = (char*) malloc(sizeof(char)*1000);
    char* sender = (char*) malloc(sizeof(char)*100);
    memset(message, '\0', 1000);
    sscanf(request, "%s %s %s", type, uniq_code, receiver);
    sender = GetNameByCode(uniq_code);
    int k = 0;
    int space_number = 0;
    for(int i = 0; space_number != 3; ++i){
        if(request[i] == ' '){
            space_number++;
        }
        k++;
    }

    int l = 0;
    for(int i = k; i < strlen(request); ++i){
        message[l++] = request[i];
    }
    bool res = SendNewMessage_db(message, sender, receiver);

    memset(message, '\0', 1000);
    memset(receiver, '\0', 100);
    if (res == false){
        answer->count = 1;
        answer->Answers[0] = "ERR";
    }
    else if(res == true){
        answer->count = 1;
        answer->Answers[0] = "OK";
    }

}

void CheckNewEvents(char* request, ReqAnswer* answer){
    char type[100];
    char* code = (char*) malloc(sizeof(char)*100);
    sscanf(request, "%s %s", type, code);
    char* name = GetNameByCode(code);
    MessList* newMessages = CheckNewMessages_db(name);
    SaveOldMessagesInArchive_db(newMessages, name);
    DeleteOldMessages_db(name);
    answer->count = newMessages->count+1;
    sprintf(answer->Answers[0], "NEW_MESS %d", newMessages->count);
    char* temp = (char*) malloc(sizeof(char)*1000);
    int k = 0;
    for(int i = 1; i < answer->count; ++i){

        memset(answer->Answers[i], '\0', MAX_REQUEST_SIZE);
        strcat(answer->Answers[i], "MESS");
        strcat(answer->Answers[i], " ");
        strcat(answer->Answers[i], newMessages->sender[k]);
        strcat(answer->Answers[i], " ");
        strcat(answer->Answers[i], newMessages->messages[k]);
        strcpy(temp, answer->Answers[i]);
        k++;
    }
}

void CheckUserStatus(char* request, ReqAnswer* answer){

}

void ServInfo(char* request, ReqAnswer* answer){
    // smt more difficult later maybe...
    answer->count = 1;
    answer->Answers[0] = "Origin";
}

ReqAnswer* MainRequestHandler(char* request){
    char type[100];
    sscanf(request, "%s", type);
    ReqAnswer* answer = malloc(sizeof(ReqAnswer*));
    answer->Answers = (char**)malloc(sizeof(char*)*MAX_REQUEST_NUMBER);
    for(int i = 0; i < MAX_REQUEST_NUMBER; ++i){
        answer->Answers[i] = (char*) malloc(sizeof(char)*MAX_REQUEST_SIZE);
    }
    char func_name[100][100] = {"LOGIN", "REGISTER", "SEND", "CHECK_INFO", "CHECK_USER",
                                "SERV_INFO"};
    void (*function_pointers[6])(char*, ReqAnswer*) = {Login, Register, SendNewMess, CheckNewEvents,
                                                 CheckUserStatus, ServInfo};
    for (int i = 0; i < 6; ++i){
        if(strcmp(type, func_name[i]) == 0){
            function_pointers[i](request, answer);
        }
    }
    return answer;
}