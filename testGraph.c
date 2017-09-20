#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char* argv[]) {
	int maxV = 50;
	Graph g = newGraph(maxV);
	addEdge(g, "me", "you");
	addEdge(g, "me", "you");
	addEdge(g, "me", "she");
	addEdge(g, "she", "he");
	showGraph(g, TERSE);
	disposeGraph(g);
	return EXIT_SUCCESS;
}
