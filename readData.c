//readData.c - Reads data from files and creates a graph of the URLs
//Modified by Rahil Agrawal, September 2017
#include "readData.h"
#include "assert.h"
#define MAX_CHAR 256
#define MAX_V 100

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls() {
    Queue collectionUrls = newQueue();
    FILE *collectionFp = fopen("./Sample1/collection.txt", "r");
    assert(collectionFp != NULL);
    char str[MAX_CHAR] = {0};
    while (fscanf(collectionFp, "%s", str) != EOF) {
        enterQueue(collectionUrls, str);
        printf("Scanning...");
    }
    printf("\n");
    showQueue(collectionUrls);
    fclose(collectionFp);
    return collectionUrls;
}

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls) {
    Graph urlGraph = newGraph(MAX_V);
    char url_from[MAX_CHAR] = {0};
    char subdir[MAX_CHAR] = "./Sample1/";
    while(!emptyQueue(collectionUrls)) {
        strcpy(url_from, leaveQueue(collectionUrls));
        char url_from_location[MAX_CHAR] = {0};
        // e.g. ./Sample1/
        strcpy(url_from_location, subdir);
        // e.g. ./Sample1/url31
        strcat(url_from_location, url_from);
        // e.g. ./Sample1/url31.txt
        strcat(url_from_location, ".txt");
        FILE *nextUrlFp = fopen(url_from_location, "r");
        // We want to look for urls and ignore all other strings
        char url_to[MAX_CHAR] = {0};
        while(1) {
            // If we reach the end of the file
            if (fscanf(nextUrlFp, "%s", url_to) == EOF) {
                break;
            }
            if (strcmp(url_to, "#start") == 0) continue;
            else if (strcmp(url_to, "Section-1") == 0) continue;
            else if (strcmp(url_to, "#end") == 0) break;

            addEdge(urlGraph, url_from, url_to);
        }
    }
    showGraph(urlGraph, DENSE);
    return urlGraph;
}
