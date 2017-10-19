// graph.c - Graph of vertices using adjacency matrix
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017

#include "graph.h"

typedef unsigned char Bit;

// Each instance of this struct is a Page
typedef struct Vertex {
	char url[MAX_CHAR]; // Link/URL of the page
	int nInLinks; // Number of incoming links to the page
	int nOutLinks; // Number of outgoing links from the page
	float pagerank_before; // pagerank of page at time t
	float pagerank_after; // pagerank of page at time t+1
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
	for (int i = 0; i < maxV; i++) {
		g->vertices[i] = NULL;
		g->vertices[i] = (Vertex *)malloc(sizeof(Vertex));
		assert(g->vertices[i] != NULL);
		memset(g->vertices[i], 0, sizeof(Vertex));	// Initialise values to 0
		g->edges[i] = (Bit *)malloc(maxV * sizeof(Bit));
		assert(g->edges[i] != NULL);
		memset(g->edges[i], 0, maxV);	// Initialise all values to 0
	}

	return g;
}
// Free all malloced memory associated with the Graph
void disposeGraph(Graph g) {
	for (int i = 0; i < g->maxV; i++) {
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
	int from_index = 0, to_index = 0;
	from_index = findVertexIdFromString(g, from);
	to_index = findVertexIdFromString(g, to);
	// If from doesn't exist in the graph
	if (from_index == -1) {
		from_index = addVertex(g, from);
	}
	// If to doesn't exist in the graph
	if (to_index == -1) {
		to_index = addVertex(g, to);
	}
	if (from_index < 0 || to_index < 0) {
		printf(RED "Index out of bounds\n" RESET);
		return 0;
	}
	// Add an edge
	if(!(g->edges[from_index][to_index])){
		g->edges[from_index][to_index] += 1;
		g->vertices[to_index]->nInLinks++;
		g->vertices[from_index]->nOutLinks++;
	}

	return 1;
}

int nVertices(Graph g) {
	assert(g != NULL);
	return g->nV;
}

int isConnected(Graph g, char *from, char *to) {
	int from_index = findVertexIdFromString(g, from);
	int to_index = findVertexIdFromString(g, to);
	if (from_index == -1 || to_index == -1) return 0;
	return (g->edges[from_index][to_index] != 0) ? 1 : 0;
}
// Display the graph in one of two modes:
// DENSE : Prints page name and explcitly states links
// TERSE : Shows the links between pages in a 2D array of 1s and 0s
void showGraph(Graph g, int print_mode) {
	assert(g != NULL);
	if (g->nV == 0) {
		printf("Graph is empty\n");
	}
	else {
		if (print_mode == DENSE) {
			for (int i = 0; i < g->nV; i++) {
				printf("Vertex %d: " RED "'%s'" RESET, i, getVertexUrl(g, i));
				printf(" connects to:\n");
				int isConnected = 0;
				for (int j = 0; j < g->maxV; j++) {
					// Print the same vertex for multiple edges
					for (int k = 0; k < g->edges[i][j]; k++) {
						printf("   Vertex %d: " RED "'%s'\n" RESET, j, getVertexUrl(g, j));
						isConnected = 1;
					}
				}
				if (!isConnected) printf("   Nothing\n");
			}
		}
		else if (print_mode == TERSE) {
			printf("   ");
			for (int i = 0; i < g->maxV; i++) printf("%3d", i);
			printf("\n");
			for (int i = 0; i < g->maxV; i++) {
				printf("%3d", i);
				for (int j = 0; j < g->maxV; j++) {
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
	for (int i = 0; i < g->nV; i++) {
		if (strcmp(g->vertices[i]->url, string) == 0) id = i;
	}
	return id;
}

// Return: The index at which a vertex was added, or -1 if a vertex could
// not be added
static int addVertex(Graph g, char *string) {
	// TODO: Implement insertion sort
	// If we're at the maximum number of nodes
	if (g->nV == g->maxV) {
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
int isEdge(Graph g, int from, int to){
	return g->edges[from][to];
}
// Return the number of outgoing links from a page given its VertexId
int numOutlinks(Graph g, int i){
	return g->vertices[i]->nOutLinks;
}
// Return the number of incoming links to a page given its VertexId
int numInlinks(Graph g, int i){
	return g->vertices[i]->nInLinks;
}
// Return the pagerank of a page at time t given its vertexId
float get_pagerank_before(Graph g, int i){
	return g->vertices[i]->pagerank_before;
}
// Return the pagerank of a page at time t+1 given its vertexId
float get_pagerank_after(Graph g, int i){
	return g->vertices[i]->pagerank_after;
}
// Set the pagerank of a page at time t given the pagerank and page's VertexId
void set_pagerank_before(Graph g, int i, float value){
	g->vertices[i]->pagerank_before = value;
}
// Set the pagerank of a page at time t+1 given the pagerank and page's VertexId
void set_pagerank_after(Graph g, int i, float value){
	g->vertices[i]->pagerank_after = value;
}
// Display the pageranks of all pages and the sum of the pagerank
void showPageRanks(Graph g){
	float sum = 0.0;
	FILE *fp = fopen("pagerankList.txt", "w");
	if (fp == NULL) {
        perror("Error, could not open file");
	}
	for(int i = 0; i < g->nV; i++){
		fprintf(fp, "%s, %d, %.7lf\n",
			g->vertices[i]->url,
			g->vertices[i]->nOutLinks,
			g->vertices[i]->pagerank_before);
	}
	fclose(fp);
	char sortedlist[g->maxV][MAX_CHAR];
	graphToList(g, sortedlist);
	FILE *fp2 = fopen("pagerankList.txt", "w");
	if (fp2 == NULL) {
        perror("Error, could not open file");
	}
	for(int i = 0; i < g->nV; i++){
		int vertexId = findVertexIdFromString(g, sortedlist[i]);
		sum += g->vertices[i]->pagerank_before;
		fprintf(fp2, "%s, %d, %.7lf\n",
			g->vertices[vertexId]->url,
			g->vertices[vertexId]->nOutLinks,
			g->vertices[vertexId]->pagerank_before);
	}
	fclose(fp2);
}
// Set the values Page Info
void setVertexInfo(Graph g, int vertexId, int nInLinks, int nOutLinks, float pagerank){
	g->vertices[vertexId]->pagerank_before = pagerank;
	g->vertices[vertexId]->nInLinks = nInLinks;
	g->vertices[vertexId]->nOutLinks = nOutLinks;
}

void graphToList(Graph g, char sortedlist[][MAX_CHAR]){
	List l = newList();
	for(int i = 0; i < g->nV; i++){
		appendList(l, g->vertices[i]->url, 0.0, 0);
	}
	sortList(l, cmpPagerank);
	listToArray(l, sortedlist);
}
