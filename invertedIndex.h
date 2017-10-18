// invertedIndex.h - Generate an inverted index of words from urls
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017

#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "readData.h"
#include "tree.h"
#include "queue.h"
#include "searchFunctions.h"
#include "headers.h"

// Return an inverted index as a tree
// Each vertex in the tree has a word
// Each vertex in the tree has a list of urls on which that word appears
Tree getInvertedIndex(Queue collectionUrls);

#endif
