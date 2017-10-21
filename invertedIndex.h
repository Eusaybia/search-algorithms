/*
	invertedIndex.h - Generate an inverted index of words from urls
    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/


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
