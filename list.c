// list.c - Implementation of a list of strings
// Written by Kongwei Ying, September 2017

#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

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
static void quickSort(Node *p, Node *r, int (*compar)(const void *, const void *));
static Node *partition(Node *p, Node *r, int (*compar)(const void *, const void *));
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

// Used as a comparator for sortList()
// Sorts based on the Node's string
int cmpStr(const void *p1, const void *p2) {
    return strcmp(((Node *)p1)->str, ((Node *)p2)->str);
}

// Used as a comparator for sortList()
// Sorts based on the Node's string==url's pagerank
// Reads from the pagerank file
int cmpPagerank(const void *p1, const void *p2) {
    // Open the pagerank file
    FILE *pagerankFp = fopen("pagerankList.txt", "r");
    if (pagerankFp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    // Scan all of pagerank into a buffer
    char word[MAX_CHAR] = {0};
    double pagerank1, pagerank2 = 0;
    while (1) {
        // Finish if we have both pageranks
        if (pagerank1 && pagerank2) break;
        double temp = 0;
        char outlinks[MAX_CHAR] = {0};
        // Scan the pagerankList.txt and scan strings without commas
        if (fscanf(pagerankFp, "%[^,], %[^,], %lf%*c", word, outlinks, &temp) == EOF) break;
        // printf("Word: %s\n", word);
        // printf("Outlinks: %s\n", outlinks);
        // printf("Temp: %lf\n", temp);
        // Look for the first url
        if (strcmp(word, ((Node *)p1)->str) == 0) {
            pagerank1 = temp;
        }
        // Look for the second url
        else if (strcmp(word, ((Node *)p2)->str) == 0) {
            pagerank2 = temp;
        }
    }
    // if (!pagerank1 && !pagerank2) {
    //     printf("Pageranks not found!");
    // }
    // printf("pgrank1: %lf\n", pagerank1);
    // printf("pgrank2: %lf\n", pagerank2);
    if (pagerank1 == pagerank2) return 0;
    return (pagerank1 - pagerank2 > 0) ? -1 : 1;
}

// Sort list using an arbitrary comparator function
void sortList(List l, int (*compar)(const void *, const void *)) {
    quickSort(l->head, l->tail, compar);
}

static void quickSort(Node *p, Node *r, int (*compar)(const void *, const void *)) {
    if (r != NULL && p != r && p != r->next) {
        Node *q = partition(p, r, compar);
        quickSort(p, q->prev, compar);
        quickSort(q->next, r, compar);
    }
}

// p is the beginning of the list, r is the end
// A more concise implementation of the Lomuto partition on CLRS p171
// as it removes the unnecessary i + 1 offset
static Node *partition(Node *p, Node *r, int (*compar)(const void *, const void *)) {
    Node *pivot = r;
    Node *i = p;
    for (Node *j = p; j != r; j = j->next) {
        if (compar(j, pivot) <= 0) {
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

// delimiter controls what elements are printed with
// nNodes controls how many elements are printed (-1 prints all elements)
void showList(List l, FILE *fp, char delimiter, int *nNodes) {
    Node *n = l->head;

    if (n == NULL) {
        fprintf(fp, "List is empty");
    }

    while (n != NULL && *nNodes != 0) {
        fprintf(fp, "%s%c", n->str, ((n->next!=NULL && *nNodes!=1) ? delimiter : ' '));
        n = n->next;
        *nNodes = *nNodes - 1;
    }
    fprintf(fp, "\n");
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

void listToArray(List l, char sortedlist[][MAX_CHAR]){
    assert(l!=NULL);
    int counter = 0;
    Node *curr = l->head;
    while(curr!=NULL){
        strcpy(sortedlist[counter++],curr->str);
        curr = curr->next;
    }
}
