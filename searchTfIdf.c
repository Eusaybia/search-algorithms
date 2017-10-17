//Written by Dennis Gann, October 2017

#include "searchTfIdf.h"
#include "colours.h"
#include "pagerank.h"
#include "readData.h"
#include "list.h"
#include "invertedIndex.h"
#include "graph.h"
#include <math.h>

int main(int argc, char * argv[]) {
    Queue collectionUrls1 = getCollectionUrls();
    getInvertedIndex(collectionUrls1);
    //GET QUERIES FROM COMMAND LINE ARGS
    char queries[MAX_QUERIES][MAX_CHAR] = {{0}};
    int nQueries = argc - 1;
    if (nQueries == 0) {
        perror("Please supply search terms");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        int j = 0;
        for (; argv[i][j] != '\0'; j++) {
            argv[i][j] = tolower((unsigned char)argv[i][j]);
        }
        if (argv[i][j-1] == '.' || argv[i][j-1] == ',' || argv[i][j-1] == ';' || argv[i][j-1] == '?') argv[i][j-1] = '\0';
        strcpy(queries[i-1], argv[i]);
    }


    //open invertedIndex file stream

    FILE *invertedIndexFp = fopen("invertedIndex.txt", "r");
    if (invertedIndexFp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int totalDocs = getTotalDocs("./Sample1/collection.txt");
    List urlList = newList();
    char buf[MAX_CHAR] = {0};

    while (1) {
        char invertedIndexStr[MAX_CHAR] = {0};

        // Scan every word of the invertedIndex
        if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == EOF)
            break;

        // If the query matches the word in the index, load the word's urls
        char matchedUrlList[MAX_V][MAX_CHAR] = {{0}};
        int nMatchedUrls = 0;

        for (int i = 0; i < nQueries; i++) {
            if (strcmp(invertedIndexStr, queries[i]) == 0) {
                //scanned word matches one of query terms

                // Read the rest of the line into buf
                memset(buf, 0, MAX_CHAR);
                fgets(buf, MAX_CHAR, invertedIndexFp);
                // Then extract the strings and place them into matchedUrlList
                char *url = NULL;
                url = strtok(buf, " ");
                for (int j = 0; url != NULL && j < MAX_QUERIES; j++) {
                    // Remove non-char characters such as new lines from the string
                    if (sscanf(url, "%s", url) == EOF) break;
                    strcpy(matchedUrlList[j], url);
                    nMatchedUrls++;
                    // printf("%d\n", nMatchedUrls);
                    url = strtok(NULL, " ");
                }

                for (int j = 0; j < nMatchedUrls; j++) {

                    char subdir[MAX_CHAR] = "./Sample1/";
                    char url_from_location[MAX_CHAR] = {0};
                    // e.g. ./Sample1/
                    strcpy(url_from_location, subdir);
                    // e.g. ./Sample1/url31
                    strcat(url_from_location, matchedUrlList[j]);
                    // e.g. ./Sample1/url31.txt
                    strcat(url_from_location, ".txt");
                    FILE *urlToOpen = fopen(url_from_location, "r");

                    double tfidf = getTfIdf(queries[i], urlToOpen, nMatchedUrls, totalDocs);
                    //printf("%s %.6lf\n", matchedUrlList[j], tfidf);
                    addTfIdf(urlList, matchedUrlList[j], tfidf, 1);

                    fclose(urlToOpen);

                }
            }
        }
    }

    fclose(invertedIndexFp);
    //sortList(urlList, cmpNum);
    showTfIdfList(urlList, stdout, 30);
    return EXIT_SUCCESS;
 }


double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs) {

     //declare and initialise variables
     int docLength = 0;
     int tc = 0;
     double tf = 0;
     double idf  = 0;
     double tfidf = 0;

     char curr_word[MAX_CHAR] = {0};

     while (1) {
         // If we reach the end of the file
         if (fscanf(doc, "%s", curr_word) == EOF) {
             break;
         }

         if (strcmp(curr_word, "#start") == 0) continue;
         // Skip words with first 7 letters "Section"
         else if (strncmp(curr_word, "Section", 7) == 0) continue;
         // Skip words with first 3 letters "url"
         else if (strncmp(curr_word, "url", 3) == 0) continue;
         else if (strcmp(curr_word, "#end") == 0) continue;

         // normalise words - Convert word to lower case and remove full stops
         for (int i = 0; curr_word[i] != '\0'; i++) {
             curr_word[i] = tolower((unsigned char)curr_word[i]);
             if (curr_word[i] == '.') curr_word[i] = '\0';
             if (curr_word[i] == ',') curr_word[i] = '\0';
             if (curr_word[i] == ';') curr_word[i] = '\0';
             if (curr_word[i] == '?') curr_word[i] = '\0';

         }

         if (strcmp(curr_word, term) == 0) {
             tc++;
         }

         docLength++;

     }

     tf = (double) tc/docLength;
     idf = log10((double)totalDocs/totalMatchedUrls);
     tfidf = tf * idf;

     return tfidf;

 }


//usage e.g. getTotalDocs("./Sample1/collection.txt")
 int getTotalDocs(char * filePath) {

     FILE *collectionFp = fopen(filePath, "r");
     assert(collectionFp != NULL);
     char str[MAX_CHAR] = {0};
     int totalDocs = 0;
     while (fscanf(collectionFp, "%s", str) != EOF) {
        totalDocs++;
     }
     fclose(collectionFp);
     return totalDocs;

}
