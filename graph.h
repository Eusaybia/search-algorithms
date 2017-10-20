// graph.h - Interface to Graph of strings
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, Sept-Oct 2017
#ifndef GRAPH_H
#define GRAPH_H

#define DENSE 0
#define TERSE 1
#include "headers.h"
#include "list.h"
#include "colours.h"

typedef struct GraphRep *Graph;

Graph   newGraph(int maxV);
void 	disposeGraph(Graph g);
int 	addEdge(Graph g, char *from, char *to);
int 	nVertices(Graph g);
int 	isConnected(Graph g, char *from, char *to);
int 	isEdge(Graph g, int from, int to);
int		numOutlinks(Graph g, int i);
int		numInlinks(Graph g, int i);
double	get_pagerank_before(Graph g, int i);
double	get_pagerank_after(Graph g, int i);
void 	set_pagerank_after(Graph g, int i, double value);
void 	set_pagerank_before(Graph g, int i, double value);
void 	showPageRanks(Graph g);
void 	showGraph(Graph g, int print_mode);
void	setVertexInfo(Graph g, int vertexId, int numInlinks, int numOutlinks, double pagerank);
char    *getVertexUrl(Graph g, int vertexId);
void	setVertexUrl(Graph g, char *string, int vertexId);
void 	graphToList(Graph g, char sortedlist[][MAX_CHAR]);
int     findVertexIdFromString(Graph g, char *string);

#endif
