// pagerank.h - Functions to calculate pagerank
// Written by Rahil Agrawal, September 2017

#ifndef PAGERANK_H
#define PAGERANK_H

#include "headers.h"
#include "graph.h"
#include "invertedIndex.h"

void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g);
float pageRankIncoming(Graph g, int i);
float Win(Graph g, int j, int i);
float Wout(Graph g, int j, int i);

#endif
