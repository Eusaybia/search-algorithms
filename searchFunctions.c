// searchFunctions.c : Common functions in Part 1 and 2
// Written by Rahil Agrawal, October 2017

#include "searchFunctions.h"

void normalize(char strings[MAX_CHAR]){
    int j    = 0;
    for (; strings[j] != '\0'; j++) {
        strings[j] = tolower((unsigned char)strings[j]);
    }
    if (strings[j-1] == '.' || strings[j-1] == ',' || strings[j-1] == ';' || strings[j-1] == '?') strings[j-1] = '\0';
}

void getQueries(int argc, char* argv[], char queries[MAX_QUERIES][MAX_CHAR]){
    for (int i = 1; i < argc; i++) {
        normalize(argv[i]);
        strcpy(queries[i-1], argv[i]);
    }
}
