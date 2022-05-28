//
// Created by daniil on 5/17/22.
//

#include "MessageList.h"

#include <malloc.h>
#include <string.h>

char* SendMessageAnswerMaker(MessList* lst, int mess_index){
    char* answer = (char*)malloc(sizeof(char)*1200);
    sprintf(answer, "MESS");
    strcat(answer, " ");
    strcat(answer, lst->sender[mess_index]);
    strcat(answer, " ");
    strcat(answer, lst->messages[mess_index]);
    return answer;
}