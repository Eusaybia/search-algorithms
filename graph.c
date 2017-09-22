// graph.c - Graph of vertices using adjacency matrix
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "colours.h"
#define MAX_CHAR 256

typedef unsigned char Bit;

typedef struct Vertex {
	char url[MAX_CHAR];
	int w_in;
	int w_out;
	double pagerank_before;
	double pagerank_after;
} Vertex;

typedef struct GraphRep {
	int nV;				// Current number of vertices
	int maxV;			// Max number of vertices
	Vertex **vertices;	// Array of Vertex objects
	Bit **edges;		// 2D array of Bits
} GraphRep;

static int findVertexIdFromString(Graph g, char *string);
static int addVertex(Graph g, char *string);

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
	g->edges[from_index][to_index] += 1;
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
		printf("\n\n");
		printf("Initilising all Pageranks to 1......\n");
		for(int i = 0; i < g->nV; i++) printf("Pagerank for %s = %lf\n", g->vertices[i]->url, g->vertices[i]->pagerank_before);
		printf("\n\n");
	}
}

char *getVertexUrl(Graph g, int vertexId) {
	return g->vertices[vertexId]->url;
}

void setVertexUrl(Graph g, char *string, int vertexId) {
	strcpy(g->vertices[vertexId]->url, string);
	g->vertices[vertexId]->pagerank_before = 1.0;
	int w_in = 0, w_out = 0;
	for (int k = 0; k< g->nV; k++){
		if(g->edges[k][vertexId]) w_in++;
		if(g->edges[vertexId][k]) w_out++;
	}
	g->vertices[vertexId]->w_in = w_in;
	g->vertices[vertexId]->w_out = w_out;
}

// Return: The vertex id with the string, or -1 if it couldn't be found
static int findVertexIdFromString(Graph g, char *string) {
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
	return g->nV++;
}
