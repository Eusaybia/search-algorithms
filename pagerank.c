// pagerank.c - Calculate pageranks
// Written by Rahil Agrawal, September 2017


#include "pagerank.h"

#define MAX_V 100
#define MAX_CHAR 256

void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g) {
	//TODO: Write pageRankWeights function
	// N = number of Urls in Graph
	int N = g->nV;
	// Initialise pageranks of all pages to 1/N
	for (int i = 0; i < g->nV ; i++) g->vertices[i]->pagerank_before = 1.0/N;
	int iteration = 0;
	double diff = diffPR;
	double new_diff = 0.0;
	while (iteration < maxIterations && diff >= diffPR){
		new_diff = 0.0;
		for (int i = 0; i< g->nV; i++){
			g->vertices[i]->pagerank_after = (1.0 - damp)/N + damp*pageRankIncoming(g, i);
		}
		for (int i = 0; i < g->nV; i++){
			new_diff += abs(g->vertices[i]->pagerank_after - g->vertices[i]->pagerank_before);
		}
		iteration += 1;
		diff = new_diff;
	}
}

float pageRankIncoming(Graph g, int i){
	float product = 1.0;
	float sum = 0.0;
	for(int j = 0; j < g->nV ; j++){
		if(g->edges[j][i]){
			product = product * g->vertices[j]->pagerank_before * Win(g, j, i) * Wout(g, j, i);
			sum += product;
		}

	}
	return sum;
}

float Win(Graph g, int j, int i){
	int Inlinks_I = g->vertices[i]->w_in;
	int Inlinks_Sum = 0;
	for (int k = 0; k<g->nV; k++){
		if(g->edges[j][k]){
			Inlinks_Sum += g->vertices[k]->w_in;
		}
	}
	return Inlinks_I*1.0/Inlinks_Sum;
}

float Wout(Graph g, int j, int i){
	int Outlinks_I = g->vertices[i]->w_out;
	int Outlinks_Sum = 0;
	for (int k = 0; k<g->nV; k++){
		if(g->edges[j][k]){
			Outlinks_Sum += g->vertices[k]->w_out;
		}
	}
	return Outlinks_I*1.0/Outlinks_Sum;
}
