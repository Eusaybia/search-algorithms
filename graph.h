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
int 	isEdge(Graph g, int from, int to);
int		numOutlinks(Graph g, int i);
int		numInlinks(Graph g, int i);
float	get_pagerank_before(Graph g, int i);
float	get_pagerank_after(Graph g, int i);
void 	set_pagerank_after(Graph g, int i, float value);
void 	set_pagerank_before(Graph g, int i, float value);
void 	showPageRanks(Graph g);
void 	showGraph(Graph g, int print_mode);
void	setVertexInfo(Graph g, int vertexId, int numInlinks, int numOutlinks, float pagerank);
char    *getVertexUrl(Graph g, int vertexId);
void	setVertexUrl(Graph g, char *string, int vertexId);

#endif
