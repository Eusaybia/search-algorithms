// Written by Rahil Agrawal, September 2017
// Modified by Rahil Agrawal, Ocotober 2017

#ifndef SEARCHPAGERANKH_H
#define SEARCHPAGERANKH_H
#include "headers.h"

// Finds urls from invertedIndex that contain query words
// Fills matchedUrlList with urls
// Returns number of queries
int findMatchedUrls(char matchedUrlList[MAX_V][MAX_CHAR], char queries[MAX_V][MAX_CHAR], int nQueries);

// Orders matchedUrlList according to pagerankList
void findPagerank(int nQueries, char matchedUrlList[MAX_V][MAX_CHAR]);
#endif
