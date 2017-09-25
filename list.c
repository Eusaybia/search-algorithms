// list.c - Implementation of a list of strings
// Written by Kongwei Ying, September 2017

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 256

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    char *str;
} Node;

typedef struct ListRep {
    struct Node *head;
    struct Node *tail;
} ListRep;

static int isElementList(List l, char *str);
static void quickSort(Node *p, Node *r);
static Node *partition(Node *p, Node *r);
static void swap(Node *n1, Node *n2); 
static Node *newNode(char *str);

List newList() {
    List l = malloc(sizeof(struct ListRep));
    l->head = NULL;
    l->tail = NULL;

    return l;
}

void dropList(List l) {
    Node *n = l->head;
    while (n != NULL) {
        Node *next = n->next;
        free(n->str);
        free(n);
        n = next;
    }
    free(l);
}

int isEmpty(List l) {
    return (l->head == NULL) ? 1 : 0;
}

void appendList(List l, char *str) {
    // We want the list to be a set
    if (isElementList(l, str)) return;

    if (isEmpty(l)) {
        l->head = newNode(str);
        l->tail = l->head;
    }
    else if (l->head == l->tail) {
        l->head->next = newNode(str);
        l->tail = l->head->next;

        l->tail->prev = l->head;
    }
    else {
        Node *new = newNode(str);
        new->prev = l->tail;
        l->tail->next = new;
        l->tail = new;
    }
}

static int isElementList(List l, char *str) {
    Node *n = l->head;
    while (n != NULL) {
        if (strcmp(n->str, str) == 0) {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

int deleteFromList(List l, char *str) {
    Node *curr = l->head;
    // Attempt to find the node
    while (curr != NULL && strcmp(curr->str, str) != 0) {
        curr = curr->next;
    }
    if (curr != NULL) {
        if (l->head == l->tail) {
            free(curr->str);
            free(curr);
            l->head = NULL;
            l->tail = NULL;
        }
        else {
            if (curr->prev == NULL) {
                l->head = curr->next;
            }
            if (curr->next == NULL) {
                l->tail = curr->prev;
            }
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            }
            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            }
            free(curr->str);
            free(curr);
        }
        return 1;
    }
    else return 0; // String not in list
}

void sortList(List l) {
    quickSort(l->head, l->tail);
}

static void quickSort(Node *p, Node *r) {
    if (r != NULL && p != r && p != r->next) {
        Node *q = partition(p, r);
        quickSort(p, q->prev);
        quickSort(q->next, r);
    }
}

// p is the beginning of the list, r is the end
// A more concise implementation of the Lomuto partition on CLRS, p171
// Removes the i + 1 offset
static Node *partition(Node *p, Node *r) {
    Node *pivot = r;
    Node *i = p;
    for (Node *j = p; j != r; j = j->next) {
        if (strcmp(j->str, pivot->str) <= 0) {
            swap(i, j);
            i = i->next;
        }
    }
    swap(i, r);
    return i;
}

static void swap(Node *n1, Node *n2) {
    char temp[MAX_CHAR] = {0};
    strcpy(temp, n1->str);
    strcpy(n1->str, n2->str);
    strcpy(n2->str, temp);
}

void showList(List l) {
    Node *n = l->head;

    if (n == NULL) {
        printf("List is empty");
    }

    while (n != NULL) {
        printf("%s ", n->str);
        n = n->next;
    }
    printf("\n");
/*     
    // Debug mode
    printf("Forward : ");
    printf("(");
    Node *n = l->head;
    while (n != NULL) {
        printf("%s", n->str);
        if (n->next != NULL) printf(",");
        n = n->next;
    }
    printf(")\n");
    printf("Backward: ");
    printf("(");
    n = l->tail;
    while (n != NULL) {
        printf("%s", n->str);
        if (n->prev != NULL) printf(",");
        n = n->prev;
    }
    printf(")\n"); */
}

// Creates a new node
static Node *newNode(char *str) {
    Node *n = malloc(sizeof(struct Node));
    n->next = NULL;
    n->prev = NULL;

    // TODO: Need to change and use centralised MAX_CHAR across all files!
    n->str = malloc(sizeof(char) * MAX_CHAR);
    memset(n->str, 0, sizeof(char) * MAX_CHAR);

    strcpy(n->str, str);

    return n;
}