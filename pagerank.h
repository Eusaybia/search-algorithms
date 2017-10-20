// pagerank.h - Functions to calculate pagerank
// Written by Rahil Agrawal, September 2017

#ifndef PAGERANK_H
#define PAGERANK_H

#include "headers.h"
#include "graph.h"
#include "invertedIndex.h"

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
