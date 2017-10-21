/*
    searchTfIdf.h - Function prototypes for functions used in searchTfIdf.c
    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#ifndef SEARCHTFIDF_H
#define SEARCHTFIDF_H

#include "headers.h"
#include "list.h"
#include "searchFunctions.h"

//Calculates the tfidf value for a given term in a fileStream doc
double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs);

//gets the total number of docs in supplied collection (filePath)
int getTotalDocs(char * filePath);

//checks correct number of commandline arguments are given
int argsOk(int argc, char *argv[]);


#endif
