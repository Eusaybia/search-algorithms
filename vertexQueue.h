/*
    vertexqueue.h ... interface to a Queue of vertices

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


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
