//readData.c - Reads data from files and creates a graph of the URLs
//Modified by Rahil Agrawal, September 2017
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

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls) {
    Graph urlGraph = newGraph(MAX_V);
    char url_from[MAX_CHAR] = {0};
    while(!emptyQueue(collectionUrls)) {
        strcpy(url_from, leaveQueue(collectionUrls));
        char url_from_location[MAX_CHAR] = {0};
        strcat(url_from_location, url_from);
        strcat(url_from_location, ".txt");
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
            char url_to_location[MAX_CHAR] = {0};
            strcat(url_to_location, url_to);
            strcat(url_to_location, ".txt");
            FILE *urlTo = fopen(url_to_location, "r");
            if(urlTo == NULL) {
                continue;
            }
            fclose(urlTo);
            if(strcmp(url_from,url_to))
                addEdge(urlGraph, url_from, url_to);
        }
        fclose(nextUrlFp);
    }
    //showGraph(urlGraph, DENSE);
    return urlGraph;
}
