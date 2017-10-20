// readData.c - Reads data from files and creates a graph of the URLs
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017
#include "readData.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls() {
    Queue collectionUrls = newQueue();
    FILE *collectionFp = fopen("./collection.txt", "r");
    assert(collectionFp != NULL);
    char str[MAX_CHAR] = {0};
    while (fscanf(collectionFp, "%s", str) != EOF) {
        enterQueue(collectionUrls, str);
    }
    fclose(collectionFp);
    return collectionUrls;
}

// Get the file directory of a url
// e.g. "url31" -> "./url31.txt"
void nameToDirectory(char *urlDirectory, char *url) {
    // e.g. ./
    strcpy(urlDirectory, "./");
    // e.g. ./url31
    strcat(urlDirectory, url);
    // e.g. ./url31.txt
    strcat(urlDirectory, ".txt");
}

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls) {
    Graph urlGraph = newGraph(MAX_V);
    char url_from[MAX_CHAR] = {0};
    while(!emptyQueue(collectionUrls)) {
        strcpy(url_from, leaveQueue(collectionUrls));
        char url_from_location[MAX_CHAR] = {0};
        nameToDirectory(url_from_location, url_from);
        FILE *nextUrlFp = fopen(url_from_location, "r");
        if(!nextUrlFp) {
            fprintf(stderr, "Couldn't open %s\n", url_from_location);
            exit(0);
        }
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

            if(strcmp(url_from,url_to))
                addEdge(urlGraph, url_from, url_to);
        }
    }
    //showGraph(urlGraph, DENSE);
    return urlGraph;
}
