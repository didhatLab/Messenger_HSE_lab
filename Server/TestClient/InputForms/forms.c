//
// Created by daniil on 5/9/22.
//
#include <stdio.h>
#include <malloc.h>
#include "forms.h"

User * get_user_info(){
    User* user = (User*) malloc(sizeof(User));
    user->login = (char*) malloc(sizeof(char)*100);
    user->password = (char*) malloc(sizeof(char)*100);
    user->type = (char*) malloc(sizeof(char)*100);
    printf("Input your login: ");
    scanf("%s", user->login);
    printf("Input your password: ");
    scanf("%s", user->password);
    user->type = "LOGIN";
    return user;
}