#include <stdio.h>

// Finds urls from invertedIndex that contain query words
// Returns a string array of urls
char **findMatchedUrls(FILE *invertedIndexFp, char **queryWords);

// Orders matchedUrlList according to pagerankList
// Returns a string array of urls
char **findPagerank(FILE *pagerankListFp, char **matchedUrlList);