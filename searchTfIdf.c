//Written by Dennis Gann, October 2017

#include "searchTfIdf.h"
#include "colours.h"
#include "pagerank.h"
#include "readData.h"
#include <math.h>

int main(int argc, char * argv[]) {


    //open invertedIndex file stream

    FILE *invertedIndexFp = fopen("invertedIndex.txt", "r");
    if (invertedIndexFp == NULL) {
        perror("Error opening file");
        exit(1);
    }


    //GET QUERIES FROM USER
    char queries[MAX_QUERIES][MAX_CHAR] = {{0}};
    char buf[MAX_CHAR] = {0};
    int nQueries = 0;

    // Scan queries
    printf(RED "\n\n               Welcome to Yaggle. Enter your tf-idf search query.\n" RESET);
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
        if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == EOF)
            break;
        // If the query matches the word in the index, load the word's urls
        for (int i = 0; i < nQueries; i++) {
            char matchedUrlList[MAX_V][MAX_CHAR] = {{0}};
            int nMatchedUrls = 0;

            if (strcmp(invertedIndexStr, queries[i]) == 0) {

                printf("%s:\n", queries[i]);

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


                    //printf("%s -- TC: %d, length: %d TF: %lf, IDF: %lf, TFIDF: %lf \n", matchedUrlList[k], tc, length, tf, idf, tfidf);
                    printf("%s -- TfIdf: %lf\n", matchedUrlList[j], getTfIdf(queries[i], urlToOpen, nMatchedUrls, 7));

                }
            }
        }
    }


    fclose(invertedIndexFp);









     return EXIT_SUCCESS;
 }


double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs) {

     //declare and initialise variables
     int docLength = 0;
     int tc = 0;
     double tf = 0;
     double idf  = 0;
     double tfidf = 0;

     //normalise search term
     for (int i = 0; term[i] != '\0'; i++) {
         term[i] = tolower((unsigned char)term[i]);
     }

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
         }

         if (strcmp(curr_word, term) == 0) {
             tc++;
         }

         docLength++;

     }

     tf = (double) tc/docLength;
     idf = log((double)totalDocs/totalMatchedUrls);
     tfidf = tf * idf;

     return tfidf;

 }
