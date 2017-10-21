// searchFunctions.h : Functions that are common to both Part 1 and 2
// Written by Rahil Agrawal, October 2017

#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include "headers.h"

// normalise - Remove trailing punctuations from the end of the word
void normalise(char strings[MAX_CHAR]);

// normalise the command line arguments and store them in a string array
int getQueries(int argc, char* argv[], char queries[MAX_QUERIES][MAX_CHAR]);

#endif
