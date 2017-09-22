// readData.h - initialises the web graph and inverted index BST
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#include "tree.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls();

// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls);

// Generate empty inverted index BST
// TODO: Create BST list structure