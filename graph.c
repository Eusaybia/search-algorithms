// graph.c - Graph of vertices using adjacency matrix
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017

#include "graph.h"

typedef unsigned char Bit;

// Each instance of this struct is a Page
typedef struct Vertex {
	char url[MAX_CHAR];	// Link/URL of the page
	int nInLinks;	// Number of incoming links to the page
	int nOutLinks;	// Number of outgoing links from the page
	double pagerankBefore;	// pagerank of page at time t
	double pagerankAfter;	// pagerank of page at time t+1
} Vertex;

typedef struct GraphRep {
	int nV;				// Current number of vertices
	int maxV;			// Max number of vertices
	Vertex **vertices;	// Array of Vertex objects
	Bit **edges;		// 2D array of Bits
} GraphRep;


static int addVertex(Graph g, char *string);
// Create a new Graph and initialise data as required
Graph newGraph(int maxV) {
	GraphRep *g = (GraphRep *)malloc(maxV * sizeof(GraphRep));
	assert(g != NULL);

	// Initialise all members
	g->maxV = maxV;
	g->nV = 0;
	g->vertices = (Vertex **)malloc(maxV * sizeof(Vertex *));
	assert(g->vertices != NULL);
	g->edges = (Bit **)malloc(maxV * sizeof(Bit *));
	assert(g->edges != NULL);

	// Malloc memory for vertices and edges arrays
	for (int i = 0; i < maxV; i++){
		g->vertices[i] = NULL;
		g->vertices[i] = (Vertex *)malloc(sizeof(Vertex));
		assert(g->vertices[i] != NULL);
		memset(g->vertices[i], 0, sizeof(Vertex));		// Initialise values to 0
		g->edges[i] = (Bit *)malloc(maxV * sizeof(Bit));
		assert(g->edges[i] != NULL);
		memset(g->edges[i], 0, maxV);	// Initialise all values to 0
	}

	return g;
}

// Free all malloced memory associated with the Graph
void disposeGraph(Graph g) {
	for (int i = 0; i < g->maxV; i++){
		free(g->vertices[i]);
		free(g->edges[i]);
	}
	free(g->vertices);
	free(g->edges);
	free(g);
}

// Return: 1 if edge successfully added, 0 if unsuccessful
int addEdge(Graph g, char *from, char *to) {
	// Check if both vertices exist
	int fromIndex = 0, toIndex = 0;
	fromIndex = findVertexIdFromString(g, from);
	toIndex = findVertexIdFromString(g, to);
	// If from doesn't exist in the graph
	if (fromIndex == -1){
		fromIndex = addVertex(g, from);
	}
	// If to doesn't exist in the graph
	if (toIndex == -1){
		toIndex = addVertex(g, to);
	}
	if (fromIndex < 0 || toIndex < 0){
		printf(RED "Index out of bounds\n" RESET);
		return 0;
	}
	// Add an edge
	if (!(g->edges[fromIndex][toIndex])){
		g->edges[fromIndex][toIndex] += 1;
		g->vertices[toIndex]->nInLinks++;
		g->vertices[fromIndex]->nOutLinks++;
	}

	return 1;
}

int nVertices(Graph g) {
	assert(g != NULL);
	return g->nV;
}

int isConnected(Graph g, char *from, char *to) {
	int fromIndex = findVertexIdFromString(g, from);
	int toIndex = findVertexIdFromString(g, to);
	if (fromIndex == -1 || toIndex == -1) return 0;
	return (g->edges[fromIndex][toIndex] != 0) ? 1 : 0;
}

// Display the graph in one of two modes:
// DENSE : Prints page name and explcitly states links
// TERSE : Shows the links between pages in a 2D array of 1s and 0s
void showGraph(Graph g, int printMode) {
	assert(g != NULL);
	if (g->nV == 0){
		printf("Graph is empty\n");
	}
	else {
		if (printMode == DENSE){
			for (int i = 0; i < g->nV; i++){
				printf("Vertex %d: " RED "'%s'" RESET, i, getVertexUrl(g, i));
				printf(" connects to:\n");
				int isConnected = 0;
				for (int j = 0; j < g->maxV; j++){
					// Print the same vertex for multiple edges
					for (int k = 0; k < g->edges[i][j]; k++){
						printf("   Vertex %d: " RED "'%s'\n" RESET, j, getVertexUrl(g, j));
						isConnected = 1;
					}
				}
				if (!isConnected) printf("   Nothing\n");
			}
		}
		else if (printMode == TERSE){
			printf("   ");
			for (int i = 0; i < g->maxV; i++) printf("%3d", i);
			printf("\n");
			for (int i = 0; i < g->maxV; i++){
				printf("%3d", i);
				for (int j = 0; j < g->maxV; j++){
					if (g->edges[i][j] != 0) printf(RED "%3d" RESET, g->edges[i][j]);
					else printf("%3d", g->edges[i][j]);
				}
				printf("\n");
			}
		}
	}
}

// Returns the url of a page given the vertexId
char *getVertexUrl(Graph g, int vertexId) {
	return g->vertices[vertexId]->url;
}

// Sets the url of a page given its vertexId
void setVertexUrl(Graph g, char *string, int vertexId) {
	strcpy(g->vertices[vertexId]->url, string);
}

// Return: The vertex id with the string, or -1 if it couldn't be found
int findVertexIdFromString(Graph g, char *string) {
	// TODO: After addVertex implements insertion sort, implement binary search
	int id = -1;
	for (int i = 0; i < g->nV; i++){
		if (strcmp(g->vertices[i]->url, string) == 0) id = i;
	}
	return id;
}

// Return: The index at which a vertex was added, or -1 if a vertex could
// not be added
static int addVertex(Graph g, char *string) {
	// TODO: Implement insertion sort
	// If we're at the maximum number of nodes
	if (g->nV == g->maxV){
		printf(RED "Could not add vertex, graph is full\n" RESET);
		return -1;
	}
	// Copy string into the next available vertex
	setVertexUrl(g, string, g->nV);
	//Initialise page info
	setVertexInfo(g, g->nV, 0, 0, 1.0);
	return g->nV++;
}

// Check if there is an edge between two pages given the VertexIds
int isEdge(Graph g, int from, int to) {
	return g->edges[from][to];
}

// Return the number of outgoing links from a page given its VertexId
int numOutlinks(Graph g, int i) {
	return g->vertices[i]->nOutLinks;
}

// Return the number of incoming links to a page given its VertexId
int numInlinks(Graph g, int i) {
	return g->vertices[i]->nInLinks;
}

// Return the pagerank of a page at time t given its vertexId
double getPagerankBefore(Graph g, int i) {
	return g->vertices[i]->pagerankBefore;
}

// Return the pagerank of a page at time t+1 given its vertexId
double getPagerankAfter(Graph g, int i) {
	return g->vertices[i]->pagerankAfter;
}

// Set the pagerank of a page at time t given the pagerank and page's VertexId
void setPagerankBefore(Graph g, int i, double value) {
	g->vertices[i]->pagerankBefore = value;
}

// Set the pagerank of a page at time t+1 given the pagerank and page's VertexId
void setPagerankAfter(Graph g, int i, double value) {
	g->vertices[i]->pagerankAfter = value;
}

// Display the pageranks of all pages and the sum of the pagerank
void showPageRanks(Graph g) {
	char sortedlist[g->maxV][MAX_CHAR];
	graphToList(g, sortedlist);
	// Open pageranks.txt in write mode
	FILE *fp = fopen("pagerankList.txt", "w");
	if (fp == NULL){
		perror("Error, could not open file");
	}
	// Write sorted pageranks in the following format:
	// url string, number of outlinks, pagerank to 7dp
	// Eg: url12, 7, 0.04567123
	for (int i = 0; i < g->nV; i++){
		int vertexId = findVertexIdFromString(g, sortedlist[i]);
		fprintf(fp, "%s, %d, %.7lf\n",
				g->vertices[vertexId]->url,
				g->vertices[vertexId]->nOutLinks,
				g->vertices[vertexId]->pagerankBefore);
	}
	fclose(fp);
}

// Set the values Page Info
void setVertexInfo(Graph g, int vertexId, int nInLinks, int nOutLinks, double pagerank) {
	g->vertices[vertexId]->pagerankBefore = pagerank;
	g->vertices[vertexId]->nInLinks = nInLinks;
	g->vertices[vertexId]->nOutLinks = nOutLinks;
}

// Create a List, the nodes of which emulate the Vertices of the graph
// This is done to use the sorting algrithms written for lists
// and write pageranks in a sorted order
void graphToList(Graph g, char sortedlist[][MAX_CHAR]) {
	List l = newList();
	for (int i = 0; i < g->nV; i++){
		// Create list with the url strings and pageranks values as the main
		// components of the nodes
		appendList(l, g->vertices[i]->url, g->vertices[i]->pagerankBefore, 0);
	}
	// Sort the list in descending order of PageRankValues
	sortList(l, cmpPagerankValues);
	// Convert the list to an array of strings
	listToArray(l, sortedlist);
	dropList(l);
}
