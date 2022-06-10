#include "UuidGenerator.h"
#include "stdlib.h"

void get_unique_code(char **base) {
    static int current_number = 0;
    current_number++;
    char *temp  = (char*)malloc(sizeof(char) * 100);
    int size_temp = 0;
    int i = 0, copy_of_number = current_number;
    while (copy_of_number) {
        temp[size_temp++] = (copy_of_number % 10) + 48;
        copy_of_number /= 10;
    }
    while (size_temp) {
        *base[i++] = temp[size_temp-1];
    }
    free(temp);
}
