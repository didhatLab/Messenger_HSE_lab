//
// Created by daniil on 5/8/22.
//
#include <malloc.h>
#include <string.h>
#include "user.h"

void* user_into_list(User* user){
    void** list = (void*) malloc(sizeof (void)* 3);
    list[0] = user->type;
    list[1] = user->login;
    list[2] = user->password;
    return list;
}

char* user_into_string(User* user){
    unsigned int new_string_len = strlen(user->password) + strlen(user->login) +
                                  strlen(user->type) + 3;
    int n = 0;
    char* new_string = (char*) malloc(sizeof(char) * new_string_len);
    void** list_fields = user_into_list(user);
    for (int i = 0; i < 3; ++i){
        char* s = (char*)list_fields[i];
        for (int j = 0; j < strlen(s); ++j){
            new_string[n++] = s[j];
        }
        new_string[n++] = ' ';
    }
    new_string[n] = '\0';
    return new_string;
}
