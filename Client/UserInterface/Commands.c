//
// Created by daniil on 5/10/22.
//

#include "Commands.h"
#include <stdio.h>
#include <malloc.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include "../structures/Friends/Freinds.h"
#include "../DataBaseController/dbController.h"
#include "../RequestHandler/HelpScripts/RequestMaker.h"
#include "../RequestHandler/Main/RequestHandler.h"
#include "../GlobalConfigs/configs.h"
#include "../structures/Message/message.h"


bool ShowFriends(){
    UserList* friends_list = get_list_friends_db();
    printf("-----------UserList List-------------\n");
    for (int i = 0; i < friends_list->quantity; ++i){
        printf("%s\n", friends_list->user_list[i]);
    }
    return true;
}

bool AddNewFriend(){
    char sub_command[40];
    scanf("%s", sub_command);
    char* name = (char*) malloc(sizeof(char)*100);
    if (strcmp(sub_command, "friend") == 0){
        printf("\nInput friend's name: ");
        scanf("%s", name);
        //checking user in server
        bool res = addFreind_db(name);
        if (res == true){
            printf("<%s> added to friends list", name);
        }
        return res;
    }
    else{
        char answ[3];
        printf("Unknown command... Maybe you mean command 'add friend'?[y/n]\n>");
        scanf("%s", answ);
        if (strcmp(answ, "n") == 0){
            return false;
        }
        else if(strcmp(answ, "y") == 0){
            printf("\nInput friend's name: ");
            scanf("%s", name);
            bool res = addFreind_db(name);
            if(res == true){
                printf("<%s> added to friends list", name);
            }
            return res;
        }
        else{
            printf("illegal answer\n");
            return false;
        }
    }
    return false;
}

bool DeleteFriend(){
    char* name = (char*)malloc(sizeof(char)*100);
    char sub_command[30];
    scanf("%s", sub_command);
    if (strcmp(sub_command, "friend") == 0){
        printf("Input friend's name for deleting: ");
        scanf("%s", name);
        bool res = delFriend_db(name);
        if (res == true){
            printf("<%s> deleted from friends\n", name);
            free(name);
            return true;
        }
        else{
            free(name);
            printf("error with deleting\n");
        }
    }
    else{
        free(name);
        printf("Unknown command\n");
        return false;
    }

    return false;
}

bool DeleteDialogWith(){
    char* dialogName = (char*)malloc(sizeof(char)*100);
    printf("Input dialog's name: ");
    scanf("%s", dialogName);
    bool res = delDialogWith_db(dialogName);
    if (res){
        printf("dialog <%s> deleted\n", dialogName);
    }
    return res;
}

bool DelHandler(){
    char function_name[100][100] = {"friend", "dialog"};
    bool (*delFunc_pointers[4])() = {DeleteFriend, DeleteDialogWith};
    char sub_command[100];
    scanf("%s", sub_command);

    for (int i = 0; i < 2; ++i){
        if(strcmp(sub_command, function_name[i]) == 0){
            delFunc_pointers[i]();
        }
    }

}


bool Exit(){
    exit(0);
}

bool sendMess(){
    char ch;
    int k = 0;
    char* receiver = (char*)malloc(sizeof(char)* 100);
    size_t lenmax = 1000, len = lenmax;
    printf("Input receiver: ");
    scanf("%s", receiver);
    char* mess = (char*) malloc(sizeof(char)*1000);
    char* word = (char*) malloc(sizeof(char)*100);
    memset(mess, '\0', 1000);
    scanf("%s", word);
    while(strcmp(word, "/end") != 0){
        strcat(mess, word);
        strcat(mess, " ");
        scanf("%s", word);
    }
    addNewMess_db(receiver, user_info_globalConfig->login, mess);
    char* request = SengMessegeMaker(uniq_code_globalConfig, receiver, mess);
    send_request(serv_globalConfig, request);
    sendOkMess(serv_globalConfig) ;
    memset(mess, '\0', 1000);
    memset(word, '\0', 100);
    memset(request, '\0', 1000);

    return false;
}

bool SendNewObject(){
    char sub_command[30];
    scanf("%s", sub_command);

    char send_items[100][100] = {"mess", "file"};
    bool (*functions_for_send[4])() = {sendMess};

    for(int i = 0; i < 2; ++i){
        if (strcmp(sub_command, send_items[i]) == 0){
            functions_for_send[i]();
        }
    }
    return true;
}

bool ShowDialogWith(){
    char* UserName = (char*) malloc(sizeof(char)*100);
    scanf("%s", UserName);
    Message_list* mes_list = getDialogWith_db(UserName);
    for(int i = 0; i < mes_list->count; ++i){
        printf("%s: %s\n",mes_list->sender[i], mes_list->mess[i]);
    }
    free(mes_list);
    free(UserName);
    return true;
}
bool ShowDialogs(){
    UserList * dialogs = get_list_diologs_db();
    printf("<Dialogs>\n");
    for(int i = 0; i < dialogs->quantity; ++i){
        printf("%s\n", dialogs->user_list[i]);
    }
    free(dialogs);
    return true;
}

bool ShowHandler(){
    char sub_command[100];
    scanf("%s", sub_command);
    char function_names[100][100] = {"dialogs", "dialog", "friends"};
    bool (*function_pointers[5])() = {ShowDialogs, ShowDialogWith, ShowFriends};
    for (int i = 0; i < 3; ++i){
        if (strcmp(function_names[i],sub_command) == 0){
            function_pointers[i]();
        }
    }
    return true;
}

bool CheckNewMessages(){
    char* request = CheckMaker(uniq_code_globalConfig);
    char* s = send_request(serv_globalConfig, request);
    sendOkMess(serv_globalConfig);
    process_answer(s);
    return true;
}

void CommandHandler(){
    char* command = (char*)malloc(sizeof(char)*100);
    char functions_name[100][100] = {"/friends", "/add", "/dell", "/exit",
                                     "/send", "/show", "/check"};
    bool (*function_pointers[7])()= {ShowFriends, AddNewFriend, DelHandler, Exit,
                                     SendNewObject, ShowHandler, CheckNewMessages};


    while(1){
        scanf("%s", command);
        for (int i = 0; i < 7; ++i){
            if (strcmp(command, functions_name[i]) == 0){
                function_pointers[i]();

            }
        }
    }

}
