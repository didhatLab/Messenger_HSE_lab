//
// Created by daniil on 5/23/22.
//

#include "StartConfiguration.h"

#include "../GlobalConfigs/GlobalCOnfigs.h"
#include "../HelpScripts/HelpScripts.h"
#include <malloc.h>
void StartConfiguration(){
    code_name_globalConfig = (char**)malloc(sizeof(char*)*100);
    for(int i =0; i < 100; ++i){
        code_name_globalConfig[i] = (char*) malloc(sizeof(char)*100);
    }
    code_list_globalConfig = (char**)malloc(sizeof(char*)*100);
    for(int i =0; i < 100; ++i){
        code_list_globalConfig[i] = (char*) malloc(sizeof(char)*100);
    }



}