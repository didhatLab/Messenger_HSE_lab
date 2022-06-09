//
// Created by daniil on 5/17/22.
//

#include "dbController.h"
#include "../HelpScripts/HelpScripts.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

sqlite3* openDB(){
    sqlite3* db;
    char* ZZZZErrMsg;
    int rc;
    rc = sqlite3_open("dbServ.db", &db);
    if(rc){
        fprintf(stderr, "Can't open data base: %s\n", sqlite3_errmsg(db));
    }

    return db;
}

bool CheckCorrectUserData_db(char* usrName, char* usrPassword){
    sqlite3 * db = openDB();
    char sql[300];
    sqlite3_stmt* statement;
    char* escapedUserName = DuplicateStringWithEscaping(usrName, strlen(usrName));
    char* escapedUserPassword = DuplicateStringWithEscaping(usrPassword, strlen(usrPassword));
    sprintf(sql, "SELECT name FROM users WHERE name = '%s' AND password = '%s'", escapedUserName, escapedUserPassword);
    int rc = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &statement, NULL);
    if (rc == SQLITE_OK){
        if (sqlite3_step(statement) == SQLITE_ROW){
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return true;
        }
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    free(escapedUserName);
    free(escapedUserPassword);
    return false;
}

MessList* CheckNewMessages_db(char* usrName) {
    sqlite3 *db = openDB();
    char sql[300];
    sqlite3_stmt *statement;
    MessList *msgList = malloc(sizeof(MessList *));

    msgList->messages = (char **) malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; ++i) {
        msgList->messages[i] = (char *) malloc(sizeof(char) * 1000);
    }
    msgList->sender = (char **) malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; ++i) {
        msgList->sender[i] = (char *) malloc(sizeof(char) * 100);
    }

    char* escapedUserName = DuplicateStringWithEscaping(usrName, strlen(usrName));
    sprintf(sql, "SELECT message, sender FROM newMessages WHERE receiver='%s'", escapedUserName);
    int rc = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &statement, NULL);
    int k = 0;
    while (sqlite3_step(statement) == SQLITE_ROW) {



        // Loop through all the selected columns : first_name (i=0), last_name (i=1), birthday (i=3)
        for (int i = 0; i < sqlite3_column_count(statement); ++i) {

            if (sqlite3_column_type(statement, i) == SQLITE_NULL) {

                switch (i) {
                    case 0: // mess
                        strcpy(msgList->messages[k], "(null)");
                        break;

                    case 1: // sender
                        strcpy(msgList->sender[k], "unknown");
                        break;


                }
            } else {

                switch (i) {
                    case 0: // mess
                        strcpy(msgList->messages[k], (const char *) sqlite3_column_text(statement, i));
                        break;

                    case 1: // sender
                        strcpy(msgList->sender[k], (const char *) sqlite3_column_text(statement, i));
                        break;


                }
            }
        }
        k++;
    }
    msgList->count = k;
    sqlite3_finalize(statement);
    //sqlite3_close(db);
    free(escapedUserName);
    return msgList;
}

bool DeleteOldMessages_db(char* usrName){
    sqlite3 *db = openDB();
    char sql[300];
    sqlite3_stmt *statement;
    char* escapedUserName = DuplicateStringWithEscaping(usrName, strlen(usrName));
    sprintf(sql, "DELETE from newMessages WHERE receiver = '%s' ", escapedUserName);
    int rc = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &statement, NULL);
    if(rc == SQLITE_OK){
        rc = sqlite3_step(statement);
    }
    else{
        fprintf(stderr, "Can't delete old messages");
        sqlite3_close(db);
        sqlite3_finalize(statement);
        return false;
    }
    sqlite3_close(db);
    sqlite3_finalize(statement);
    free(escapedUserName);
    return true;
}

bool SaveOldMessagesInArchive_db(MessList* msg_list, char* receiver){
    sqlite3 *db = openDB();
    char sql[3000];
    sqlite3_stmt *statement;
    char* escapedReceiver = DuplicateStringWithEscaping(receiver, strlen(receiver));
    for (int i =0; i < msg_list->count; ++i){
        char* escapedMessage = DuplicateStringWithEscaping(msg_list->messages[i], strlen(msg_list->messages[i]));
        char* escapedSender = DuplicateStringWithEscaping(msg_list->sender[i], strlen(msg_list->sender[i]));
        sprintf(sql, "INSERT INTO ArchiveMessages (message, sender, receiver) VALUES('%s', '%s', '%s')",
                escapedMessage, escapedSender, escapedReceiver);
        int rc = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &statement, NULL);
        if(rc == SQLITE_OK){
            rc = sqlite3_step(statement);
            sqlite3_finalize(statement);
        }
        else{
            fprintf(stderr, "Can't delete old messages");
            sqlite3_close(db);
            sqlite3_finalize(statement);
            free(escapedMessage);
            free(escapedReceiver);
            free(escapedSender);
            return false;
        }
        free(escapedMessage);
        free(escapedSender);
    }
    sqlite3_close(db);
    free(escapedReceiver);
    return true;
}

bool SendNewMessage_db(char* message, char* sender, char* receiver){
    sqlite3 *db = openDB();
    char sql[300];
    sqlite3_stmt *statement;
    char* escapedMessage = DuplicateStringWithEscaping(message, strlen(message));
    char* escapedSender = DuplicateStringWithEscaping(sender, strlen(sender));
    char* escapedReceiver = DuplicateStringWithEscaping(receiver, strlen(receiver));
    sprintf(sql, "INSERT INTO newMessages (message, sender, receiver) VALUES('%s', '%s', '%s')",
            escapedMessage, escapedSender, escapedReceiver);
    int rc = sqlite3_prepare_v2(db, sql, (int)sizeof(sql), &statement, NULL);
    if (rc == SQLITE_OK){
        rc = sqlite3_step(statement);
    }
    else{
        printf("Error with sending message...\n");
        sqlite3_finalize(statement);
        sqlite3_close(db);
        free(escapedMessage);
        free(escapedSender);
        free(escapedReceiver);
        return false;
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    free(escapedMessage);
    free(escapedSender);
    free(escapedReceiver);
    return true;
}
