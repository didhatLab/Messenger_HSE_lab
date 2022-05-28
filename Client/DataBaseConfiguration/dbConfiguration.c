//
// Created by daniil on 5/23/22.
//

#include "dbConfiguration.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

bool CreateTable(sqlite3* db, char* instruction){

    char* sql = instruction;
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, sql, (int)strlen(sql), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);
        sqlite3_finalize(statement);
        return true;

    } else {
        fprintf(stderr, "Can't initialize the database: %s\n", sqlite3_errmsg(db));
        return false;
    }
    return true;
}

//bool CreateMessageTable(sqlite3* db){
//    const char* sql = "CREATE TABLE \"messages\" (\n"
//                      "\t\"message\"\tBLOB,\n"
//                      "\t\"sender\"\tTEXT NOT NULL,\n"
//                      "\t\"receiver\"\tTEXT NOT NULL,\n"
//                      "\t\"id\"\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE\n"
//                      ");";
//    sqlite3_stmt* statement;
//    int rc = sqlite3_prepare_v2(db, sql, (int)strlen(sql), &statement, NULL);
//    if(rc == SQLITE_OK) {
//        rc = sqlite3_step(statement);
//        sqlite3_finalize(statement);
//        return true;
//
//    } else {
//        fprintf(stderr, "Can't initialize the database: %s\n", sqlite3_errmsg(db));
//        return false;
//    }
//    return true;
//
//}


bool dbConfigurate_db(){
    sqlite3* db = openDB();
    char sql[800];
    int number_tables = 3;
    char functions_name_for_creating_table[100][100] = {"Users", "messages", "friends"};
    char instruction_list[100][1000] = {"CREATE TABLE \"Users\" (\n"
                                        "\t\"Name\"\tTEXT NOT NULL,\n"
                                        "\t\"Password\"\tTEXT NOT NULL,\n"
                                        "\t\"AdditionalInfo\"\tBLOB,\n"
                                        "\t\"id\"\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE\n"
                                        ");", "CREATE TABLE \"messages\" (\n"
                                            "\t\"message\"\tBLOB,\n"
                                            "\t\"sender\"\tTEXT NOT NULL,\n"
                                            "\t\"receiver\"\tTEXT NOT NULL,\n"
                                            "\t\"id\"\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE\n"
                                            ");", "CREATE TABLE \"friends\" (\n"
                                                  "\t\"name\"\tTEXT NOT NULL,\n"
                                                  "\t\"friend_id\"\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE\n"
                                                  ");"};
    //bool (*functions_for_creating_tables[100])(sqlite3*) = {CreateTableUsers};
    sqlite3_stmt* statement;
    bool existingList[3] = {false, false, false};
    char* table_name = (char*)malloc(sizeof(char)*100);
    sprintf(sql, "SELECT name FROM sqlite_master WHERE type = 'table'");
    int rc = sqlite3_prepare_v2(db, sql, (int)strlen(sql), &statement, NULL);
    if (rc == SQLITE_OK){
        while(sqlite3_step(statement) == SQLITE_ROW){
            strcpy(table_name, (const char*) sqlite3_column_text(statement, 0));
            for(int i = 0; i < number_tables; ++i){
                if(strcmp(table_name, functions_name_for_creating_table[i]) == 0){
                    existingList[i] = true;

                }
            }
            memset(table_name, '\0', 100);
        }

    }
    for(int i = 0; i < number_tables; ++i){
        if(existingList[i] == false){
            CreateTable(db, instruction_list[i]);
        }
    }
    sqlite3_close(db);
    sqlite3_finalize(statement);

    return true;
}
