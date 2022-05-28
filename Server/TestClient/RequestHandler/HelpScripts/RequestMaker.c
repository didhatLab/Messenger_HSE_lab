//
// Created by daniil on 5/9/22.
//

#include "RequestMaker.h"
#include <string.h>
#include <malloc.h>

char* list_into_string(void** list, int list_len){
    char* new_string = (char*) malloc(sizeof(char)*800);
    int k = 0;
    for (int i = 0; i < list_len; ++i){
        char* s = (char*)list[i];
        for(int j = 0; j < strlen(s); ++j){
            new_string[k++] = s[j];
        }
        new_string[k++] = ' ';
    }
    new_string[k++] = '\0';
    return new_string;
}

char* SengMessegeMaker(char* uniq_code, char* reciever, char* mess){
    char* request= (char*) malloc(sizeof(char)*1000);
    char* type = (char*)malloc(sizeof(char)*50);
    int len_list = 4;
    strcpy(type, "SEND");
    sprintf(request, "%s %s %s %s", type, uniq_code, reciever, mess);
    //strcpy(request, mess);
    //free(request);
    //free(type);
    return request;
}

char* CheckMaker(char* uniq_code){
    char* request;
    char* type = (char*)malloc(sizeof(char)*50);
    void** list = (void*) malloc(sizeof (void)* 3);
    int len_list = 2;
    strcpy(type, "CHECK_INFO");
    list[0] = type;
    list[1] = uniq_code;
    request = list_into_string(list, len_list);

    return request;
}

char* RegisterFormMaker(){
    char* request = (char*)malloc(sizeof(char)*1000);
    char* type = "REGISTER";
    void** list = (void*) malloc(sizeof (void)* 3);
    int len_list = 2;
    //do yourself this shit
    //"REGISTER <Name> <Password>" - request form
    return request;
}