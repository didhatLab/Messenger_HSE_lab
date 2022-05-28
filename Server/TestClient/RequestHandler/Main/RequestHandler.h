//
// Created by daniil on 5/9/22.
//

#ifndef TESTCLIENT_REQUESTHANDLER_H
#define TESTCLIENT_REQUESTHANDLER_H

#endif //TESTCLIENT_REQUESTHANDLER_H
#include "../../structures/Connection/connection_data.h"
#pragma once


char* send_request(connection_data* data, char* request);
int process_answer(char* answer);
int get_uniq_code(char* answer, int n);
int receive_new_mess(char* request, int n);