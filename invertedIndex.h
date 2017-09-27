// invertedIndex.h - Generate an inverted index of words from urls
// Written by Kongwei Ying, September 2017

#include "readData.h"
#include "tree.h"
#include "queue.h"

// Return an inverted index as a tree
// Each vertex in the tree has a word
// Each vertex in the tree has a list of urls on which that word appears
Tree getInvertedIndex(Queue collectionUrls);
