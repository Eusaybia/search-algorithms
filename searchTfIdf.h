// Written by Dennis Gann, October 2017

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
