
#ifndef TESTCLIENT_USER_H
#define TESTCLIENT_USER_H

#endif //TESTCLIENT_USER_H
#pragma once


typedef struct user User;

typedef void*(*f1_t)(User*);

struct user
{

    //f1_t f2;
    char *type;
    char *login;
    char *password;
};

void* user_into_list(User* user);
char* user_into_string(User* user);
