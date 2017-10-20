// readData.c - Reads data from files and creates a graph of the URLs
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017
#include "readData.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls() {
	// Create queue of urls from the collection file
	Queue collectionUrls = newQueue() ;
	FILE *collectionFp = fopen("./collection.txt", "r") ;
	assert(collectionFp != NULL) ;
	char str[MAX_CHAR] = {0} ;
	while (fscanf(collectionFp, "%s", str) != EOF){
		enterQueue(collectionUrls, str) ;
	}
	fclose(collectionFp) ;
	return collectionUrls ;
}

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls) {
	Graph urlGraph = newGraph(MAX_V) ;
	char url_from_location[MAX_CHAR] = {0} ;
	char url_from[MAX_CHAR] = {0} ;
	char url_to[MAX_CHAR] = {0} ;
	// open one page at a time and add the edges to all the urls in that file
	while (!emptyQueue(collectionUrls)){
		strcpy(url_from, leaveQueue(collectionUrls)) ;
		strcpy(url_from_location, url_from) ;
		strcat(url_from_location, ".txt") ;
		FILE *nextUrlFp = fopen(url_from_location, "r") ;
		if (nextUrlFp == NULL){
			fprintf(stderr, "Couldn't open %s\n", url_from_location) ;
			continue ;
		}
		// Scan urls in url_from Section-1 into string url_to
		while (fscanf(nextUrlFp, "%s", url_to) != EOF){
			// Look for urls in Section-1
			if (strcmp(url_to, "#start") == 0) continue ;
			else if (strcmp(url_to, "Section-1") == 0) continue ;
			else if (strcmp(url_to, "#end") == 0) break ;
			// Only add an edge if the destination page exists
			char url_to_location[MAX_CHAR] = {0} ;
			strcpy(url_to_location, url_to) ;
			strcat(url_to_location, ".txt") ;
			FILE *urlTo = fopen(url_to_location, "r") ;
			if (urlTo == NULL) continue ;
			else fclose(urlTo) ;
			// Only add edges if url_from and url_to are distinct
			if (strcmp(url_from, url_to) != 0)
				addEdge(urlGraph, url_from, url_to) ;
		}
		fclose(nextUrlFp) ;
	}
	disposeGraph(urlGraph);
	return urlGraph ;
}
