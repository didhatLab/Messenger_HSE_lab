//
// Created by daniil on 5/17/22.
//

#include "starApp.h"
#include "../RequestHandler/Main/RequestHandler.h"
#include "../InputForms/forms.h"
#include "../structures/User/user.h"
#include "../RequestHandler/HelpScripts/RequestMaker.h"
#include <sqlite3.h>
#include "../DataBaseController/dbController.h"
#include "../UserInterface/Commands.h"
#include "../GlobalConfigs/configs.h"
#include "../DataBaseConfiguration/dbConfiguration.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>


char* MakeDbName(char* ServName, char* usrName){
    char* dbName = (char*) malloc(sizeof(char)*100);
    strcat(dbName, ServName);
    strcat(dbName, usrName);
    strcat(dbName, ".db");
    return dbName;
}

void StarWork(){
    connection_data* serv_data;
    input_serv* serv = get_serv_info();
    serv_data = connect_to_server(serv);
    if (serv_data > 0){ printf("server found\n");}
    char* serv_name = send_request(serv_data, "SERV_INFO");
    sendOkMess(serv_data);
    printf("Server's name: %s\n", serv_name);
    User* data_user = get_user_info();
    dbName_globalConfig = MakeDbName(serv_name, data_user->login);
    dbConfigurate_db();

    char* s = send_request(serv_data, user_into_string(data_user));
    sendOkMess(serv_data);
    get_uniq_code(s);
    printf("\n%s\n", s);
    serv_globalConfig = serv_data;
    user_info_globalConfig = data_user;
}