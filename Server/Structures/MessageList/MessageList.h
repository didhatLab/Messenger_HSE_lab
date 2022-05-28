//
// Created by daniil on 5/17/22.
//

#ifndef TESTSERVER_MESSAGELIST_H
#define TESTSERVER_MESSAGELIST_H

#endif //TESTSERVER_MESSAGELIST_H
#pragma once
#include <time.h>

typedef struct MessList{
    char** messages;
    char** sender;
    time_t* time_messages;
    int count;
}MessList;

char* SendMessageAnswerMaker(MessList* lst, int mess_index);