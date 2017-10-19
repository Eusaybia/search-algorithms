// Written by Dennis Gann, October 2017
// Modified by Rahil Agrawal, October 2017

#include "headers.h"
#include "list.h"
#ifndef SEARCHTFIDF_H
#define SEARCHTFIDF_H

double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs);
int getTotalDocs(char * filePath);


#endif
