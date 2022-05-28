//
// Created by daniil on 5/9/22.
//

#include "connection_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


void * get_in_addr(struct sockaddr * sa){
    if (sa->sa_family == AF_INET){
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



input_serv* get_serv_info(){
    input_serv* data = (input_serv*) malloc(sizeof(input_serv));
    char* port = malloc(sizeof(char)*INET6_ADDRSTRLEN);
    char* ip = malloc(sizeof(char)*INET6_ADDRSTRLEN);
    printf("Input server IP: ");
    scanf("%s", ip);
    printf("Input server Port: ");
    scanf("%s", port);
    data->Port = port;
    data->IP = ip;
    //validation maybe
    return data;
}

connection_data* connect_to_server(input_serv* serv){
    int sockfd;
    char buf;
    struct addrinfo *hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    connection_data* res = (connection_data*)malloc(sizeof(connection_data*));
    res->servinfo = (struct addrinfo*) malloc(sizeof (struct addrinfo*));
    hints = (struct addrinfo*) malloc(sizeof (struct addrinfo*));

    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(serv->IP, serv->Port, hints, &servinfo)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(-1);
    }

    for (p = servinfo; p != NULL; p = p->ai_next){
        if ((res->sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
            perror("client");
            continue;
        }

        if (connect(res->sockfd, p->ai_addr, p->ai_addrlen) == -1){
            close(res->sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }
    if (p == NULL){
        fprintf(stderr, "client: failed to connect");
        exit(1);
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr), s, sizeof s);
    char g[100];
    int num;
    res->servinfo = servinfo;
    freeaddrinfo(servinfo);

    return res;
}

int close_connection(connection_data* connection){
    freeaddrinfo(connection->servinfo);
    close(connection->sockfd);
    free(connection);
    return 0;
}