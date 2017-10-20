// queue.h ... interface to a Queue of vertices
// Written by John Shepherd, September 2015
// Modified by Kongwei Ying, September 2017

#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"
#include "headers.h"
typedef struct QueueRep *VertexQueue;

// Create new VertexQueue
VertexQueue newVertexQueue();
// Free the VertexQueue and all memory associated with it
void disposeVertexQueue(VertexQueue);
// Add a new string to the VertexQueue
void enterVertexQueue(VertexQueue, Vertex *);
// Get the first item from the VertexQueue
Vertex *leaveVertexQueue(VertexQueue);
// Return 1 if VertexQueue is empty, 0 otherwise
int emptyVertexQueue(VertexQueue);
// Display the VertexQueue to stdout
void showVertexQueue(VertexQueue q);

#endif
