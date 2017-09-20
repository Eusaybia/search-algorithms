#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagerank.h"
#include "graph.h"
#define MAX_V 100
#define MAX_CHAR 256

int main(int argc, char *argv[]) {
	// TODO: Read web pages from the collection file and build graph
	// Build graph

	// TODO: Sum of all pages' PR = 1

	double damp = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIterations = atoi(argv[3]);

	//pageRankWeights(damp, diffPR, maxIterations);

	return EXIT_SUCCESS;
}

void pageRankWeights(double damp, double diffPR, int maxIterations) {
	//TODO: Write pageRankWeights function
}
