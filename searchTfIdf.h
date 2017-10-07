//Written by Dennis Gann, October 2017
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define MAX_CHAR 256
#define MAX_QUERIES 256
#define MAX_V 256



#ifndef SEARCHTFIDF_H
#define SEARCHTFIDF_H

double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs);


#endif
