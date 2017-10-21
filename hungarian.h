/*
    hungarian.h - Function prototypes for functions used in hungarian.c

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */
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
