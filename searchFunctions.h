// searchFunctions.h : Functions that are common to both Part 1 and 2
/*
    fileName.c - File description (e.g. Graph implementation using adjacent matrix)

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include "headers.h"
#include "colours.h"
#include "pagerank.h"
#include "readData.h"
#include "list.h"
#include "invertedIndex.h"
#include "graph.h"

// normalise - Remove trailing punctuations from the end of the word
void normalise(char strings[MAX_CHAR]);

// normalise the command line arguments and store them in a string array
int getQueries(int argc, char* argv[], char queries[MAX_QUERIES][MAX_CHAR]);

#endif
