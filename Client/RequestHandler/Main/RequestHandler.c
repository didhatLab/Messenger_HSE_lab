//
// Created by daniil on 5/9/22.
//
#define MAXDATASIZE 1000


#include "RequestHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../GlobalConfigs/configs.h"
#include "../../DataBaseController/dbController.h"

char* send_request(connection_data* data, char* request){
    char* answer = (char*) malloc(sizeof(char)* 1000);
    struct addrinfo * p = data->servinfo;
    int numbytes;
    if((send(data->sockfd, request, strlen(request), 0)  == -1)){
        perror("send_request failed");
    }
    memset(answer, '\0', 1000);
    if ((numbytes = recv(data->sockfd, answer, MAXDATASIZE-1, 0) == -1)){
        perror("send_request failed");
    }
    return answer;
}

char* get_new_answer(connection_data* data){
    int numbytes;
    char* answer = (char*) malloc(sizeof(char)* 1000);
    memset(answer, '\0', 1000);
    if ((numbytes = recv(data->sockfd, answer, MAXDATASIZE-1, 0) == -1)){
        perror("send_request failed");
    }
    return answer;

}


int receive_mess(char* request){
    char* name_sender = (char*)malloc(sizeof(char)*100);
    char* mess = (char*) malloc(sizeof(char)*1000);
    char type[100];
    sscanf(request, "%s %s", type, name_sender);
    unsigned int k = strlen(type) + strlen(name_sender) + 2;
    int j = 0;
    for(unsigned int i = k; i < strlen(request); ++i){
        mess[j++] = request[i];
    }
    mess[j++] = '\0';

    addNewMess_db(user_info_globalConfig->login, name_sender, mess);
    printf("New message from %s\n", name_sender);
    return 0;
}

int get_uniq_code(char* answer){
    char* code = (char*)malloc(sizeof(char)*100);
    int k = 0;
    char type[100];
    sscanf(answer, "%s %s", type, code);
    uniq_code_globalConfig = code;
    printf("uniq code for chatting received\n");
    return 0;
}

void sendOkMess(connection_data* data){
    char* answer = (char*) malloc(sizeof(char)* 1000);
    struct addrinfo * p = data->servinfo;
    int numbytes;
    if((send(data->sockfd, "OK", 2, 0)  == -1)){
        perror("send_request failed");
    }

}

int new_mess_signal(char* answer){
    char type[40];
    char * end;
    char* mess_number = (char*) malloc(sizeof(char)*10);
    sscanf(answer, "%s %s", type, mess_number);
    int number = (int)strtol(mess_number, &end, 10);
    for(int i = 0; i < number; ++i){
        char* s = get_new_answer(serv_globalConfig);
        sendOkMess(serv_globalConfig);
        receive_mess(s);
        memset(s, '\0', strlen(s));
    }
    return 0;
}


int process_answer(char* answer){
    char type[30];
    int k = 0;
    sscanf(answer, "%s", type);
    char functions_name[100][100] = {"NEW_MESS", "MESS", "CODE"};
    int (*function_pointers[3])(char*)= {new_mess_signal,receive_mess, get_uniq_code};

    for (int i = 0; i < 3; ++i){
        if (strcmp(type, functions_name[i]) == 0){
            function_pointers[i](answer);
        }
    }
    free(answer);
    return 0;
}