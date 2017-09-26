#include "searchPagerank.h"
#include "colours.h"
#include "pagerank.h"
#include "readData.h"

// Finds urls from invertedIndex that contain query words
// Fills matchedUrlList with urls
// Returns number of matched urls
int findMatchedUrls(char matchedUrlList[MAX_V][MAX_CHAR]) {
    FILE *invertedIndexFp = fopen("invertedIndex.txt", "r");
    if (invertedIndexFp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char queries[MAX_QUERIES][MAX_CHAR] = {0};
    char buf[MAX_CHAR] = {0};
    int nQueries = 0;
    int nMatchedUrls = 0;

    // Scan queries
    fgets(buf, MAX_CHAR, stdin);
    char *query = NULL;
    query = strtok(buf, " ");
    for (int i = 0; query != NULL && i < MAX_QUERIES; i++) {
        // Remove non-char characters from the string
        if (sscanf(query, "%s", query) == EOF) break;
        strcpy(queries[i], query);
        nQueries++;
        // printf("'%s;\n", queries[i]);
        query = strtok(NULL, " ");
    }

    while (1) {
        char invertedIndexStr[MAX_CHAR] = {0};
        // Scan every word of the invertedIndex
        if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == 0)
            break;
        // If the query matches the word in the index, load the word's urls
        for (int i = 0; i < nQueries; i++) {
            if (strcmp(invertedIndexStr, queries[i]) == 0) {
                // Read the rest of the line into buf
                memset(buf, 0, MAX_CHAR);
                fgets(buf, MAX_CHAR, invertedIndexFp);
                // Then extract the strings and place them into matchedUrlList
                char *url = NULL;
                url = strtok(buf, " ");
                for (int i = 0; url != NULL && i < MAX_QUERIES; i++) {
                    // Remove non-char characters such as new lines from the string
                    if (sscanf(url, "%s", url) == EOF) break;
                    strcpy(matchedUrlList[i], url);
                    nMatchedUrls++;
                    printf("%s\n", matchedUrlList[i]);
                    url = strtok(NULL, " ");
                }
            }
        }
    }
    return nMatchedUrls;
}


// Sorts matchedUrlList according to pagerankList
// Returns a string array of urls
void findPagerank(FILE *pagerankListFp, int nMatchedUrls, char matchedUrlList[MAX_V][MAX_CHAR]) {

}
