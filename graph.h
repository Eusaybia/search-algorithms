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

// Create a new graph
Graph   newGraph(int maxV);
// Empty the graph and free all memory associated with it
void  disposeGraph(Graph g);
// Add a directed edge from url_from to url_to
int  addEdge(Graph g, char *from, char *to);
// Return the number of vertices in the graph
int  nVertices(Graph g);
// Return 1 if there is an edge from url_from to url_to, 0 otherwise
int  isConnected(Graph g, char *from, char *to);
// Same as isConnected but used vertexId instead of url strings
int  isEdge(Graph g, int from, int to);
// Returns number of outgoing links from given page
int  numOutlinks(Graph g, int i);
// Returns number of incoming links to a given page
int  numInlinks(Graph g, int i);
// Returns the pagerank of the page at time t
double getPagerankBefore(Graph g, int i);
// Returns the pagerank of the page at time t+1
double getPagerankAfter(Graph g, int i);
// Sets the pagerank of the current page at time t+1 to the supplied value
void  setPagerankAfter(Graph g, int i, double value);
// Sets the pagerank of the current page at time t to the supplied value
void  setPagerankBefore(Graph g, int i, double value);
// Write the pageranks to pagerankList.txt
void  showPageRanks(Graph g);
// Display graph to stdout in one of two modes. Mode can be supplied by user
void  showGraph(Graph g, int print_mode);
// When creating a new vertex, set the corresponding values
void setVertexInfo(Graph g, int vertexId, int numInlinks, int numOutlinks, double pagerank);
// Returns the url of a page given its vertexId
char    *getVertexUrl(Graph g, int vertexId);
// Sets the url of a vertex
void setVertexUrl(Graph g, char *string, int vertexId);
// Create a List, the nodes of which emulate a vertex of a graph
void graphToList(Graph g, char sortedlist[][MAX_CHAR]);
// Returns the Id of a vertex given its url string
int     findVertexIdFromString(Graph g, char *string);

#endif
