#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include "RequestHandler/RequestHandler.h"
#include "Structures/RequestAnswer/RequestAnswer.h"
#include "StartConfiguration/StartConfiguration.h"


#define PORT "3490"
#define BACKLOG 10

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(){
    StartConfiguration();
    fd_set master;
    fd_set read_fds;
    int fdmax;
    int sockfd, new_fd; // слушать на sock_fd, новое подключение на new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // адресная информация подключившегося
    socklen_t sin_size;
    char* buf = (char*)malloc(sizeof(char)*3000);
    int nbytes;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // использовать мой IP
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                         sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    FD_SET(sockfd, &master);
    fdmax = sockfd;
    char  remoteIP[INET6_ADDRSTRLEN];
    int newfd;
    for (;;){
        read_fds = master;
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
            perror("select");
            exit(4);
        }
        for (int i = 0; i <= fdmax; ++i){
            if (FD_ISSET(i, &read_fds)) { // Есть!!
                if (i == sockfd) {
                    // обрабатываем новые подключения
                    addrlen = sizeof remoteaddr;
                    newfd = accept(sockfd,
                                   (struct sockaddr *)&remoteaddr,
                                   &addrlen);
                    if (newfd == -1) {
                        perror("accept");}
                    else {
                        FD_SET(newfd, &master); // добавить в главный массив
                        if (newfd > fdmax) { // отслеживаем максимальный номер
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntop(remoteaddr.ss_family,
                                         get_in_addr((struct sockaddr*)&remoteaddr),
                                         remoteIP, INET6_ADDRSTRLEN),
                               newfd);
                    }
                }
                else {
                    if ((nbytes = recv(i, buf, 3000, 0)) <= 0) {
                        if (nbytes == 0) {
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // Пока!
                        FD_CLR(i, &master); // удалить из главного массива
                    } else {
                        ReqAnswer * reqAnswer = MainRequestHandler(buf);
                        for(int pol = 0; pol < reqAnswer->count; ++pol){
                            send(i, reqAnswer->Answers[pol], strlen(reqAnswer->Answers[pol]), 0);
                            recv(i, buf, 3, 0);
                        }
                        printf("%s\n", reqAnswer->Answers[0]);
                        memset(buf, '\0', 3000);
                        memset(reqAnswer, 0, sizeof(ReqAnswer));
                    }
                } // END обработка данных от клиента
            } // END есть новое входящее подключение
        } // END цикл по файловым дескрипторам
    } // END for(;;)—и вы думаете, что это не закончится!

}


