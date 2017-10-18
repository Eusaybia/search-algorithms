// queue.c ... Queue of vertices
// Written by John Shepherd, September 2015
// Modified by Kongwei Ying, September 2017


#include "vertexQueue.h"

typedef struct Node *Link;

typedef struct Node
{
	Vertex *val;
	Link next;
} Node;

typedef struct QueueRep
{
	Link front;
	Link back;
} QueueRep;

static Link newNode(Vertex *);
static void disposeNode(Link);

// newQueue()
// - create an initially empty Queue
VertexQueue newVertexQueue()
{
	VertexQueue new = malloc(sizeof(QueueRep));
	assert(new != NULL);
	new->front = NULL;
	new->back = NULL;
	return new;
}

// disposeQueue(Queue)
// - clean up memory associated with Queue
void disposeVertexQueue(VertexQueue q)
{
	if (q == NULL)
		return;
	Link next, curr = q->front;
	while (curr != NULL)
	{
		next = curr->next;
		disposeNode(curr);
		curr = next;
	}
}

// enterQueue(Queue,Str)
// - add Str to back of Queue
void enterVertexQueue(VertexQueue q, Vertex *str)
{
	Link new = newNode(str);
	if (q->front == NULL)
		q->front = q->back = new;
	else
	{
		// add into list of elems
		q->back->next = new;
		q->back = new;
	}
}

// leaveQueue(Queue)
// - return string at front of Queue
Vertex *leaveVertexQueue(VertexQueue q)
{
	assert(q->front != NULL);
	Vertex *str = q->front->val;
	Link old = q->front;
	q->front = old->next;
	if (q->front == NULL)
		q->back = NULL;
	free(old);
	return str;
}

// emptyQueue(Queue)
// - check whether Queue is empty
int emptyVertexQueue(VertexQueue q)
{
	return (q->front == NULL);
}

// showQueue(Queue)
// - display Queue (for debugging)
void showVertexQueue(VertexQueue q)
{
	Link curr;
	if (q->front == NULL)
		printf("Queue is empty\n");
	else
	{
		printf("Queue (front-to-back):\n");
		int id = 0;
		curr = q->front;
		while (curr != NULL)
		{
			printf("[%03d] %s\n", id, curr->val->word);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions

static Link newNode(Vertex *str)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = str;
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}
