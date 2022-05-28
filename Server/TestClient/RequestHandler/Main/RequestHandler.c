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

char* send_request(connection_data* data, char* request){
    char* answer = (char*) malloc(sizeof(char)* 1000);
    struct addrinfo * p = data->servinfo;
    int numbytes;
    if((send(data->sockfd, request, strlen(request), 0)  == -1)){
        perror("send_request failed");
    }
    if ((numbytes = recv(data->sockfd, answer, MAXDATASIZE-1, 0) == -1)){
        perror("send_request failed");
    }
    return answer;
}

int receive_new_mess(char* request, int n){
    char* name_sender = (char*)malloc(sizeof(char)*100);
    char* mess = (char*) malloc(sizeof(char)*1000);
    int k = 0;
    for (int i = n; request[i] != ' '; ++i){
        name_sender[k++] = request[i];
    }
    name_sender[k++] = '\0';
    int j = 0;
    for (int i = k; i < strlen(request); ++i){
        mess[j++] = request[i];
    }
    mess[j++] = '\0';
    // writing in database
    printf("New message from %s\n", name_sender);
    return 0;
}

int get_uniq_code(char* answer, int n){
    char* code = (char*)malloc(sizeof(char)*100);
    int k = 0;
    for(int i = n; i < strlen(answer); ++i){
        code[k++] = answer[i];
    }
    code[k++] = '\0';
    //writing code in db
    printf("uniq code for chatting received\n");
    return 0;
}


int process_answer(char* answer){
    char type[30];
    int k = 0;
    char functions_name[100][100] = {"MESS", "CODE"};
    int (*function_pointers[3])(char*, int)= {receive_new_mess, get_uniq_code};
    for(int i = 0; answer[i] != ' '; ++i){
        type[k++] = answer[i];
    }
    type[k++] = '\0';
    for (int i = 0; i < 2; ++i){
        if (strcmp(type, functions_name[i]) == 0){

        }
    }
    free(answer);
    return 0;
}