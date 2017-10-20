// queue.h ... interface to simple Queue of Strings
// Written by John Shepherd, September 2015

#ifndef QUEUE_H
#define QUEUE_H

#include "headers.h"

typedef struct QueueRep *Queue;

// Create a new Queue
Queue newQueue();
// Free the Queue and all memory associated with it
void disposeQueue(Queue);
// Add a new string to the Queue
void enterQueue(Queue, char *);
// Get the first item from the Queue
char *leaveQueue(Queue);
// Return 1 if Queue is empty, 0 otherwise
int emptyQueue(Queue);
// Display the Queue to stdout
void showQueue(Queue q);

#endif
