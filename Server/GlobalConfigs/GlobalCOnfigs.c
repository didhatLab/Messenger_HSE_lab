//
// Created by daniil on 5/23/22.
//

#include "GlobalCOnfigs.h"

#include <string.h>
#include <malloc.h>

#include "../HelpScripts/HelpScripts.h"

char** code_list_globalConfig;
char** code_name_globalConfig;
int list_index_globalConfigs = 0;



char* GetNameByCode(char* code){

    char* res = (char*)malloc(sizeof(char)*100);
    strcpy(res, "Unknown");
    for(int i = 0; i <  list_index_globalConfigs; ++i){
        if(strcmp(code, code_list_globalConfig[i]) == 0){
            return code_name_globalConfig[i];
        }
    }
    return res;
}






