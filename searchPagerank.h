/*
    searchPagerank.h - Function Prototypes for functions used in searchPagerank.c

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#ifndef SEARCHPAGERANKH_H
#define SEARCHPAGERANKH_H

#include "headers.h"
#include "searchFunctions.h"
// Finds urls from invertedIndex that contain query words
// Fills matchedUrlList with urls
// Returns number of queries
int findMatchedUrls(char matchedUrlList[MAX_V][MAX_CHAR], char queries[MAX_V][MAX_CHAR], int nQueries);

// Orders matchedUrlList according to pagerankList
void findPagerank(int nQueries, char matchedUrlList[MAX_V][MAX_CHAR]);
#endif
