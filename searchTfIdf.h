//Written by Dennis Gann, October 2017


#define MAX_CHAR 256
#define MAX_QUERIES 256
#define MAX_V 256

#include "headers.h"
#include "list.h"
#ifndef SEARCHTFIDF_H
#define SEARCHTFIDF_H

double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs);
int getTotalDocs(char * filePath);


#endif
