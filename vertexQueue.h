// queue.h ... interface to a Queue of vertices
// Written by John Shepherd, September 2015
// Modified by Kongwei Ying, September 2017

#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

typedef struct QueueRep *VertexQueue;

// Function signatures

VertexQueue newVertexQueue();
void disposeVertexQueue(VertexQueue);
void enterVertexQueue(VertexQueue, Vertex *);
Vertex *leaveVertexQueue(VertexQueue);
int emptyVertexQueue(VertexQueue);
void showVertexQueue(VertexQueue q);

#endif

