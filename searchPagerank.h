#include <stdio.h>
#define MAX_CHAR 256
#define MAX_QUERIES 256
#define MAX_V 256

#ifndef SEARCHPAGERANKH_H
#define SEARCHPAGERANKH_H

// Finds urls from invertedIndex that contain query words
// Fills matchedUrlList with urls
// Returns number of matched urls
int findMatchedUrls(char matchedUrlList[MAX_V][MAX_CHAR]);

// Orders matchedUrlList according to pagerankList
void findPagerank(FILE *pagerankListFp, int nMatchedUrls,
                        char matchedUrlList[MAX_V][MAX_CHAR]);
#endif
