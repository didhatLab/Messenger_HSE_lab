//
// Created by daniil on 5/17/22.
//

#ifndef TESTSERVER_DBCONTROLLER_H
#define TESTSERVER_DBCONTROLLER_H

#endif //TESTSERVER_DBCONTROLLER_H

#include <sqlite3.h>
#include <stdbool.h>
#include "../Structures/MessageList/MessageList.h"

bool CheckCorrectUserData_db(char* usrName, char* usrPassword);
MessList* CheckNewMessages_db(char* usrName);
bool DeleteOldMessages_db(char* usrName);
bool SaveOldMessagesInArchive_db(MessList* msg_list, char* receiver);
bool SendNewMessage_db(char* message, char* sender, char* receiver);
