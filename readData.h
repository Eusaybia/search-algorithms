// readData.h - initialises the web graph and inverted index BST
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017

#ifndef READDATA_H
#define READDATA_H

#include "headers.h"
#include "queue.h"
#include "graph.h"
#include "tree.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls();

// Converts a url into its directory
void nameToDirectory(char *urlDirectory, char *url);

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls);

#endif
