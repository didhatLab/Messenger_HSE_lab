//
// Created by daniil on 5/23/22.
//

#include "HelpScripts.h"
#include <malloc.h>

void FillMemoryForStringList(char** list, int elementNumber, int elementLength){
    list = (char**) malloc(sizeof(char*)*elementNumber);
    for(int i = 0; i < elementNumber; ++i){
        list[i] = (char*) malloc(sizeof(char)*elementLength);
    }
}

