// searchFunctions.c : Common functions in Part 1 and 2
// Written by Rahil Agrawal, October 2017

#include "searchFunctions.h"

// Mormalize - Remove trailing punctuations from a string
void normalise(char strings[MAX_CHAR]) {
	int i = 0;
	for (i = 0; strings[i] != '\0'; i++){
		strings[i] = tolower((unsigned char)strings[i]);
	}

	i--;
	if (strings[i] == '.' || strings[i] == ',' || strings[i] == ';' || strings[i] == '?') strings[i] = '\0';
}

// normalise the query term arguments and store them in a queries array
int getQueries(int argc, char *argv[], char queries[MAX_QUERIES][MAX_CHAR]) {
	for (int i = 1; i < argc; i++){
		normalise(argv[i]);
		strcpy(queries[i - 1], argv[i]);
	}
	return argc - 1;
}
