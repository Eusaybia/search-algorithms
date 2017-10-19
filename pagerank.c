// pagerank.c - Calculate pageranks
// Written by Rahil Agrawal, September 2017
// Modified by Rahil Agrawal, October 2017
#include "pagerank.h"
#include "readData.h"
#include "list.h"

int main(int argc, char* argv[]){
	Queue collectionUrls1 = getCollectionUrls();
    Graph urlGraph = createUrlGraph(collectionUrls1);
	if(argc!=4)
		pageRankWeights(0.85, 0.00001, 1000, urlGraph);
	else{
		char *buf;
		pageRankWeights(strtod(argv[1], &buf), strtod(argv[2], &buf), atoi(argv[3]), urlGraph);
	}
	return EXIT_SUCCESS;
}
// Base function to calculate pageranks using formula provided in
// http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html and
// http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/page1725348.pdf
void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g) {
	// N = number of Urls in Graph
	int N = nVertices(g);
	// Initialise pageranks of all pages to 1/N
	for (int i = 0; i < N ; i++) set_pagerank_before(g, i, (1.0/(double)N)); //showPageRanks(g);
	int iteration = 0;
	double diff = diffPR;
	double new_diff = 0.0;
	while (iteration < maxIterations && diff >= diffPR){
		new_diff = 0.0;
		for (int i = 0; i< N; i++){
			double value = (double)(1.0 - damp)/(double)N + damp*pageRankIncoming(g, i);
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
// Function to calculate the product of PageRank, In-weight and Out-weight
double pageRankIncoming(Graph g, int i){
	double product = 1.0;
	double sum = 0.0;
	for(int j = 0; j < nVertices(g) ; j++){
		if(isEdge(g, j, i)){
			product = get_pagerank_before(g, j) * Win(g, j, i) * Wout(g, j, i);
			sum += product;
		}

	}
	return sum;
}

// Function to calculate the In-Weight
double Win(Graph g, int j, int i){
	int Inlinks_I = numInlinks(g, i);
	int Inlinks_Sum = 0;
	for (int k = 0; k<nVertices(g); k++){
		if(isEdge(g, j, k)){
			Inlinks_Sum += numInlinks(g, k);
		}
	}
	return (double)Inlinks_I/(double)Inlinks_Sum;
}

// Function to calculate the Out-Weight
double Wout(Graph g, int j, int i){
	double Outlinks_I = (numOutlinks(g, i) ? numOutlinks(g, i) : 0.5);
	double Outlinks_Sum = 0;
	for (int k = 0; k<nVertices(g); k++){
		if(isEdge(g,j,k)){
			Outlinks_Sum += (numOutlinks(g, k) ? numOutlinks(g, k) : 0.5);
		}
	}
	return (double)Outlinks_I/(double)Outlinks_Sum;
}
