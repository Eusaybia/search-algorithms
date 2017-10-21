/*
    searchFunctions.c : Common functions in Part 1 and 2

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/


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
