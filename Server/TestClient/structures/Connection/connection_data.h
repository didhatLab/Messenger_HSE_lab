//
// Created by daniil on 5/9/22.
//

#ifndef TESTCLIENT_CONNECTION_DATA_H
#define TESTCLIENT_CONNECTION_DATA_H

#endif //TESTCLIENT_CONNECTION_DATA_H
#pragma once

typedef struct input_serv{
    char* IP;
    char* Port;
}input_serv;



typedef struct connection_data{
    struct addrinfo* servinfo;
    int sockfd;
}connection_data;



input_serv* get_serv_info();
connection_data* connect_to_server(input_serv* serv);
int close_connection(connection_data* connection);
