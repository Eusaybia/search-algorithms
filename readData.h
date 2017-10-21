/*
    readData.h - initialises the web graph and inverted index BST


    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#ifndef READDATA_H
#define READDATA_H

#include "headers.h"
#include "queue.h"
#include "graph.h"
#include "tree.h"

// Get URLs from collection.txt and put it into set
Queue getCollectionUrls();
// Generate graph from URLs
Graph createUrlGraph(Queue collectionUrls);

#endif
