//
// Created by daniil on 5/23/22.
//

#include "HelpScripts.h"
#include <malloc.h>

void FillMemoryForStringList(char** list, int elementNumber, int elementLength){
    list = (char**) malloc(sizeof(char*)*elementNumber);
    for(int i = 0; i < elementNumber; ++i){
        list[i] = (char*) malloc(sizeof(char)*elementLength);
    }
}

/**
 * @Description
 * Creates a new string with characters " and ' replaced with their escaped versions: \\" and \'
 * @param originalString string that needs to be processed
 * @param originalStringLength length of the string (without counting \\0 in the end)
 * @return returns string duplicate with replaced escaping characters
 */
char* DuplicateStringWithEscaping(const char* originalString, int originalStringLength) {
    int escapesNumber = 0;
    for (int i = 0; i < originalStringLength; ++i) {
        if (originalString[i] == '\'' || originalString[i] == '\"') {
            ++escapesNumber;
        }
    }
    char* escapedString = (char*)malloc(sizeof(char) * (originalStringLength + escapesNumber + 1));
    int currentInsertIndex = 0;
    for (int i = 0; i < originalStringLength; ++i) {
        if (originalString[i] == '\'' || originalString[i] == '\"') {
            escapedString[currentInsertIndex++] = '\\';
        }
        escapedString[currentInsertIndex++] = originalString[i];
    }
    escapedString[currentInsertIndex] = '\0';
    return escapedString;
}

