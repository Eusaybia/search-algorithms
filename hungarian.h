#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include "headers.h"

typedef struct hProblemRep *hProblem;

//Initialises hungarian problem p
hProblem newHungarian(double** costMatrix, int size);

//Free all malloced memory associated with the Hungarian problem p
void disposeHungarian(hProblem p);

//Solves Hungarian problem p
double solveHungarian(hProblem p);

// get url position for a given rank
int getUrlFromRank(hProblem p, int position, int nElems);

//Prints the current p assignment matrix to stdout
void printHungarianAssignment(hProblem p);

//Prints the current p cost matrix to stdout
void printHungarianCostMatrix(hProblem p);

#endif
