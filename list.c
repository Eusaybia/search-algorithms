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

void showList(List l) {
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
    printf(")\n");
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