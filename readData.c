
/*
    readData.c - Reads data from files and creates a graph of the URLs

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */

#include "readData.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls() {
	// Create queue of urls from the collection file
	Queue collectionUrls = newQueue();
	FILE *collectionFp = fopen("./collection.txt", "r");
	assert(collectionFp != NULL);
	char str[MAX_CHAR] = {0};
	while (fscanf(collectionFp, "%s", str) != EOF){
		enterQueue(collectionUrls, str);
	}
	fclose(collectionFp);
	return collectionUrls;
}

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls) {
	Graph urlGraph = newGraph(MAX_V);
	char urlFromLocation[MAX_CHAR] = {0};
	char *urlFrom;
	char urlTo[MAX_CHAR] = {0};
	// open one page at a time and add the edges to all the urls in that file
	while (!emptyQueue(collectionUrls)){
		urlFrom = leaveQueue(collectionUrls);
		strcpy(urlFromLocation, urlFrom);
		strcat(urlFromLocation, ".txt");
		FILE *nextUrlFp = fopen(urlFromLocation, "r");
		if (nextUrlFp == NULL){
			fprintf(stderr, "Couldn't open %s\n", urlFromLocation);
			continue;
		}
		// Scan urls in urlFrom Section-1 into string urlTo
		while (fscanf(nextUrlFp, "%s", urlTo) != EOF){
			// Look for urls in Section-1
			if (strcmp(urlTo, "#start") == 0) continue;
			else if (strcmp(urlTo, "Section-1") == 0) continue;
			else if (strcmp(urlTo, "#end") == 0) break;
			// Only add an edge if the destination page exists
			char urlToLocation[MAX_CHAR] = {0};
			strcpy(urlToLocation, urlTo);
			strcat(urlToLocation, ".txt");
			FILE *urlToFile = fopen(urlToLocation, "r");
			if (urlToFile == NULL) continue;
			else fclose(urlToFile);
			// Only add edges if urlFrom and urlTo are distinct
			if (strcmp(urlFrom, urlTo) != 0)
				addEdge(urlGraph, urlFrom, urlTo);
		}
		free(urlFrom);
		fclose(nextUrlFp);
	}
	return urlGraph;
}
