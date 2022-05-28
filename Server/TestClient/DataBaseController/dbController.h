//
// Created by daniil on 5/10/22.
//

#ifndef TESTCLIENT_DBCONTROLLER_H
#define TESTCLIENT_DBCONTROLLER_H

#endif //TESTCLIENT_DBCONTROLLER_H
#include <sqlite3.h>
#include <stdbool.h>
#include "../structures/Friends/Freinds.h"
#include "../structures/Message/message.h"
#include <time.h>

sqlite3* openDB();
bool addFreind_db(char* nameNewFreind);
UserList* get_list_friends_db();
bool delFriend_db(char* name);
bool addNewMess_db(char* reciever, char* mess);
UserList* get_list_diologs_db();
Message_list* getDialogWith_db(char* UserName);
bool delDialogWith_db(char* UserName);