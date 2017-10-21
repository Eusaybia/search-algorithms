/*
    pagerank.h - Functions to calculate pagerank

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/

#ifndef PAGERANK_H
#define PAGERANK_H

#include "headers.h"
#include "graph.h"
#include "invertedIndex.h"
#include "readData.h"
#include "list.h"

// Main algortihm to calculate pageranks
void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g);
// Calculate product of Inweight, Outweight and Pagerank of pages
// that have an outgoing link to the current page and sum the products
// of all such pages
double pageRankIncoming(Graph g, int i);
// Calculate Inweight (Formula explained in Algorithm)
double Win(Graph g, int j, int i);
// Calculate Outweight (Formula explained in Algorithm)
double Wout(Graph g, int j, int i);

#endif
