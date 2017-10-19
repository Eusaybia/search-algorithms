// searchFunctions.c : Common functions in Part 1 and 2
// Written by Rahil Agrawal, October 2017

#include "searchFunctions.h"

void normalize(char strings[MAX_CHAR]){
    int i = 0;
    for (i = 0; strings[i] != '\0'; i++) {
        strings[i] = tolower((unsigned char)strings[i]);
    }
    
    // Then go backwards
    for (int j = i; strings[j] != '\0'; j++) {
        strings[j] = tolower((unsigned char)strings[j]);
        if (strings[j] == '.' || strings[j] == ',' || strings[j] == ';' || strings[j] == '?') strings[j] = '\0';
    }
}

void getQueries(int argc, char* argv[], char queries[MAX_QUERIES][MAX_CHAR]){
    for (int i = 1; i < argc; i++) {
        normalize(argv[i]);
        strcpy(queries[i-1], argv[i]);
    }
}
