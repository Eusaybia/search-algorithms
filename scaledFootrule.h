

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
