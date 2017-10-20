// searchFunctions.h : Functions that are common to both Part 1 and 2
// Written by Rahil Agrawal, October 2017

#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include "headers.h"

// Normalize - Remove trailing punctuations from the end of the word
void normalize(char strings[MAX_CHAR]);

// Normalize the command line arguments and store them in a string array
void getQueries(int argc, char* argv[], char queries[MAX_QUERIES][MAX_CHAR]);

#endif
