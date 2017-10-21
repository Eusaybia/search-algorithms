// queue.h ... interface to simple Queue of Strings
/*
    fileName.c - File description (e.g. Graph implementation using adjacent matrix)

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
