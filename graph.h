// graph.h - Interface to Graph of strings
// Written by Kongwei Ying, September 2017

#ifndef GRAPH_H
#define GRAPH_H

#define DENSE 0
#define TERSE 1

typedef struct GraphRep *Graph;

Graph   newGraph(int maxV);
void 	disposeGraph(Graph g);
int 	addEdge(Graph g, char *from, char *to);
int 	nVertices(Graph g);
int 	isConnected(Graph g, char *from, char *to);
// Avaliable modes
//	DENSE: View node information
//	TERSE: View adjacency matrix
void 	showGraph(Graph g, int print_mode);
void	setVertexInfo(char *url, double w_in, double w_out, double pagerank);
char    *getVertexUrl(Graph g, int vertexId);
void	setVertexUrl(Graph g, char *string, int vertexId);

#endif
