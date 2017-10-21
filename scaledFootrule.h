/*
	scaledfootrule.h : Function prototypes and #defines for scaledfootrule algorithm.
    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/


#ifndef SCALEDFOOTRULE_H
#define SCALEDFOOTRULE_H

#define MAX_LISTS 100

#include "headers.h"
#include "hungarian.h"
typedef struct UrlRep *Url;

Url newUrl();
int readRankFile(char *filename, Url *array, int *maxRows, int rankListSizes[], int listNo);
int argsOk(int argc, char *argv[]);
void insertSetArray(Url *array, int *nElems, int size, Url elem);
int cmpString(const void *a, const void *b);
int findUrlPositionInRankList(Url rankArray[], Url url, int maxUrls);
double scaledFootruleDistance(int n, int p, int tc, int ti);

#endif
