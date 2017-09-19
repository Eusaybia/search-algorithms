#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagerank.h"
#include "graph.h"
#define MAX_V 100
#define MAX_CHAR 256

int main(int argc, char *argv[]) {
	// Build graph
	// TODO: Read web pages from the collection file and build graph
	// TODO: Commit to VCS system
	// TODO: Sum of all pages' PR = 1
	FILE *collection_fp = fopen("Sample1/collection.txt", "r");
	Graph g = newGraph(MAX_V);
	char url[MAX_CHAR] = {0};
	while (fscanf(collection_fp, "%s", url) != 0) {
		char subdir[MAX_CHAR];
		strcpy(subdir, "Sample1/");
		strcat(url, ".txt");
		strcat(subdir, url);
		FILE *url_fp = fopen(subdir, "w");
	}

	double damp = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIterations = atoi(argv[3]);

	//pageRankWeights(damp, diffPR, maxIterations);

	return EXIT_SUCCESS;
}

void pageRankWeights(double damp, double diffPR, int maxIterations) {
	//TODO: Write pageRankWeights function
}
