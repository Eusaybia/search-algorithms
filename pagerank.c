// pagerank.c - Calculate pageranks
// Written by Rahil Agrawal, September 2017


#include "pagerank.h"
#include <math.h>

#define MAX_V 100
#define MAX_CHAR 256

void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g) {
	//TODO: Write pageRankWeights function
	// N = number of Urls in Graph
	int N = nVertices(g);
	// Initialise pageranks of all pages to 1/N
	for (int i = 0; i < N ; i++) set_pagerank_before(g, i, (1.0/(double)N)); showPageRanks(g);
	int iteration = 0;
	double diff = diffPR;
	double new_diff = 0.0;
	while (iteration < maxIterations && diff >= diffPR){
		new_diff = 0.0;
		for (int i = 0; i< N; i++){
			float value = (1.0 - damp)*1.0/(double)N + damp*pageRankIncoming(g, i);
			set_pagerank_after(g, i, value);
		}
		for (int i = 0; i < N; i++){
			new_diff += fabs(get_pagerank_after(g, i) - get_pagerank_before(g, i));
		}
		iteration += 1;
		diff = new_diff;
		for(int i=0; i<N; i++) set_pagerank_before(g, i, get_pagerank_after(g, i));
	}
	showPageRanks(g);
}

float pageRankIncoming(Graph g, int i){
	float product = 1.0;
	float sum = 0.0;
	for(int j = 0; j < nVertices(g) ; j++){
		if(isEdge(g, j, i)){
			product = get_pagerank_before(g, j) * Win(g, j, i) * Wout(g, j, i);
			sum += product;
		}

	}
	return sum;
}

float Win(Graph g, int j, int i){
	int Inlinks_I = numInlinks(g, i);
	int Inlinks_Sum = 0;
	for (int k = 0; k<nVertices(g); k++){
		if(isEdge(g, j, k)){
			Inlinks_Sum += numInlinks(g, k);
		}
	}
	return Inlinks_I*1.0/(double) Inlinks_Sum;
}

float Wout(Graph g, int j, int i){
	int Outlinks_I = numOutlinks(g, i);
	float Outlinks_Sum = 0;
	for (int k = 0; k<nVertices(g); k++){
		if(isEdge(g,j,k)){
			Outlinks_Sum += numOutlinks(g, k);
		}
	}
	if (Outlinks_Sum == 0) Outlinks_Sum = 0.5;
	return Outlinks_I*1.0/Outlinks_Sum;
}
