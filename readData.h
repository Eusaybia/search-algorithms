// readData.h - initialises the web graph and inverted index BST
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017

#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls();

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls);

// Generate empty inverted index BST
// TODO: Create BST list structure

#endif
