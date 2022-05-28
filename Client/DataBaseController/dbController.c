//
// Created by daniil on 5/10/22.
//

#include "dbController.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "../structures/Friends/Freinds.h"
#include "../GlobalConfigs/configs.h"

#define FREIND_INSERT_QUERY_SIZE 400
#define MAX_NUMBER_FREINDS 900
#define MAX_NAME_LENGHT 100
#define MAX_LEN_INSTRUCTION 400
#define MESS_INSERT_QUERY_SIZE 1500
#define MAX_MESS_NUMBER 1000
#define MAX_MESS_LENGTH 1000

sqlite3* openDB(){
    sqlite3* db;
    char* ZZZZErrMsg;
    int rc;
    rc = sqlite3_open(dbName_globalConfig, &db);
    if(rc){
        fprintf(stderr, "Can't open data base: %s\n", sqlite3_errmsg(db));
    }

    return db;
}

UserList* get_list_friends_db(){
    sqlite3* db = openDB(); // servName_userName.db
    char sql[FREIND_INSERT_QUERY_SIZE];
    int rc;
    char** friend_list = (char**) malloc(sizeof(char*)*MAX_NUMBER_FREINDS);
    for (int i = 0; i < MAX_NUMBER_FREINDS; ++i){
        friend_list[i] = (char*) malloc(sizeof(char)*MAX_NAME_LENGHT);
    }
    UserList* friends = malloc(sizeof *friends);
    friends->user_list = friend_list;
    int k = 0;
    sqlite3_stmt* statement;
    sprintf(sql, "SELECT name FROM friends");
    unsigned int len = strlen(sql);
    rc = sqlite3_prepare_v2(db, sql, (int)len, &statement, NULL);
    if(rc == SQLITE_OK){
        while(sqlite3_step(statement) == SQLITE_ROW){
            for(int i = 0; i < sqlite3_column_count(statement); ++i){

                if(sqlite3_column_type(statement, i) == SQLITE_NULL){
                    strcpy(friend_list[k++], "unknown");
                }
                else{
                    strcpy(friend_list[k++], (const char*) sqlite3_column_text(statement, i));

                }
            }
        }
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    friends->quantity = k;
    return friends;

}




Message_list* getDialogWith_db(char* UserName){
    sqlite3 * db = openDB();
    Message_list* mes_list = (Message_list*) malloc(sizeof(Message_list));
    mes_list->mess = (char**) malloc(sizeof(char*)*MAX_MESS_NUMBER);
    mes_list->date = (time_t*) malloc(sizeof(time_t)*MAX_MESS_NUMBER);
    for(int i = 0; i < MAX_MESS_NUMBER; ++i){
        mes_list->mess[i] = (char*) malloc(sizeof(char)*MAX_MESS_LENGTH);
    }
    mes_list->sender = (char**) malloc(sizeof(char*)*MAX_MESS_LENGTH);
    for(int i = 0; i < MAX_MESS_NUMBER; ++i){
        mes_list->sender[i] = (char*) malloc(sizeof(char)*MAX_MESS_LENGTH);
    }
    char sql[MAX_LEN_INSTRUCTION];
    int rc;
    sqlite3_stmt* statement;
    sprintf(sql, "SELECT message, sender FROM messages WHERE receiver = '%s' OR sender = '%s'",
            UserName, UserName);
    int k = 0;
    unsigned int len = strlen(sql);
    rc = sqlite3_prepare_v2(db, sql, (int)len, &statement, NULL);

    while(sqlite3_step(statement) == SQLITE_ROW) {



        // Loop through all the selected columns : first_name (i=0), last_name (i=1), birthday (i=3)
        for (int i = 0; i < sqlite3_column_count(statement); ++i) {

            if (sqlite3_column_type(statement, i) == SQLITE_NULL) {

                switch (i) {
                    case 0: // first_name
                        strcpy(mes_list->mess[k], "(null)");
                        break;

                    case 1: // last_name
                        strcpy(mes_list->sender[k], "unknown");
                        break;


                }
            } else {

                switch (i) {
                    case 0: // first_name
                        strcpy(mes_list->mess[k], (const char *) sqlite3_column_text(statement, i));
                        break;

                    case 1: // last_name
                        strcpy(mes_list->sender[k], (const char *) sqlite3_column_text(statement, i));
                        break;


                }
            }
        }
        k++;
    }


    sqlite3_finalize(statement);
    sqlite3_close(db);
    mes_list->count = k;
    return mes_list;

}

bool addNewMess_db(char* reciever, char* sender, char* mess){
    sqlite3 * db = openDB();
    char sql[MESS_INSERT_QUERY_SIZE];
    int rc;
    sqlite3_stmt* statement;
    sprintf(sql, "INSERT INTO messages (sender, receiver, message) VALUES('%s', '%s', '%s')",
            sender ,reciever, mess);
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);

    } else {
        fprintf(stderr, "Can't insert messages");
        return false;
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);
    return true;
}

bool addFreind_db(char* nameNewFreind){
    sqlite3* db = openDB(); // servName_userName.db
    char sql[FREIND_INSERT_QUERY_SIZE];
    int rc;
    sqlite3_stmt* statement;
    sprintf(sql, "INSERT INTO friends (name) VALUES('%s')", nameNewFreind);

    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);

    } else {
        fprintf(stderr, "Can't insert the freinds");
        return false;
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);
    return true;
}

bool delFriend_db(char* name){
    sqlite3* db = openDB();
    char* sql = (char*) malloc(sizeof(char)*MAX_LEN_INSTRUCTION);
    sqlite3_stmt* statement;
    sprintf(sql, "DELETE from friends where name='%s'", name);
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql),&statement, NULL);
    if(rc == SQLITE_OK){
        rc = sqlite3_step(statement);
    }
    else{
        fprintf(stderr, "Can't delete freind");
        sqlite3_close(db);
        sqlite3_finalize(statement);
        return false;
    }
    sqlite3_close(db);
    sqlite3_finalize(statement);
    return true;
}



UserList* get_list_diologs_db(){
    sqlite3* db = openDB(); // servName_userName.db
    char sql[MAX_LEN_INSTRUCTION];
    int rc;
    char** user_list = (char**) malloc(sizeof(char*)*MAX_NUMBER_FREINDS*10);
    for (int i = 0; i < MAX_NUMBER_FREINDS*10; ++i){
        user_list[i] = (char*) malloc(sizeof(char)*MAX_NAME_LENGHT);
    }
    char** user_dop = (char**) malloc(sizeof(char*)*MAX_NUMBER_FREINDS*10);
    for (int i = 0; i < MAX_NUMBER_FREINDS*10; ++i){
        user_dop[i] = (char*) malloc(sizeof(char)*MAX_NAME_LENGHT);
    }

    UserList* dialogs = malloc(sizeof *dialogs);
    dialogs->user_list = user_list;
    dialogs->dop_user_info = user_dop;
    int k = 0;
    sqlite3_stmt* statement;
    sprintf(sql, "SELECT DISTINCT sender as user FROM messages WHERE sender != '%s'\n"
                           "UNION\n"
                           "SELECT DISTINCT receiver as user FROM messages WHERE receiver != '%s'",
                           user_info_globalConfig->login, user_info_globalConfig->login);
    unsigned int len = strlen(sql);
    rc = sqlite3_prepare_v2(db, sql, (int)len, &statement, NULL);
    if(rc == SQLITE_OK){
        while(sqlite3_step(statement) == SQLITE_ROW){
            for(int i = 0; i < sqlite3_column_count(statement); ++i){

                if(sqlite3_column_type(statement, i) == SQLITE_NULL){
                    strcpy(user_list[k++], "unknown");
                }
                else{
                    strcpy(user_list[k++], (const char*) sqlite3_column_text(statement, i));
//
//                    switch (i) {
//                        case 0: // name
//                            strcpy(user_list[k++], (const char*) sqlite3_column_text(statement, i));
//                            break;
//                        case 1:
//                            strcpy(user_dop[k++], (const char*) sqlite3_column_text(statement, i));
//                    }

                }
            }
        }
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    dialogs->quantity = k;
    return dialogs;

}

bool delDialogWith_db(char* UserName){
    sqlite3 * db = openDB();
    char sql[MAX_LEN_INSTRUCTION];
    int rc;
    sqlite3_stmt* statement;
    sprintf(sql, "DELETE from messages WHERE receiver='%s' OR sender='%s'", UserName, UserName);
    rc = sqlite3_prepare_v2(db, sql, (int)strlen(sql),&statement, NULL);
    if(rc == SQLITE_OK){
        rc = sqlite3_step(statement);
    }
    else{
        fprintf(stderr, "Can't delete dialog\n");
        return false;
    }
    return true;

}
