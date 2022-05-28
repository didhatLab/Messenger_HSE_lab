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
#include <stdio.h>

void StarWork(){
    connection_data* serv_data;
    input_serv* serv = get_serv_info();
    serv_data = connect_to_server(serv);
    if (serv_data > 0){ printf("server found\n");}
    User* data_user = get_user_info();
    char* s = send_request(serv_data, user_into_string(data_user));
    printf("\n%s\n", s);
    serv_globalConfig = serv_data;
    user_info_globalConfig = data_user;
}