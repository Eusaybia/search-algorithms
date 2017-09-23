// tree.c - Interface to binary search tree 
// Written by Kongwei Ying, September 2017

#include "tree.h"
#include "vertexQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 256

typedef struct TreeRep {
   struct Vertex *root; 
} TreeRep;

static int findDepth(Vertex *root);
static int vertexKeyCompare(Vertex *v1, Vertex *v2);
static Vertex *newVertex(char *str);

// TODO: Implement functions below
Tree newTree() {
    Tree t = malloc(sizeof(struct TreeRep));
    return t;
}
void dropTree(Tree t); // Frees the tree's associated memory

void insertIntoTree(Tree t, char *word) {
    Vertex *new = newVertex(word);
    // pred always trails new
    Vertex *pred = t->root;   

    if (pred == NULL) {
        t->root = new;
        return;
    }

    while (1) {
        // Check which branch pred should go down
        // If new.key < pred.key
        if (vertexKeyCompare(new, pred) == -1) {
            // If pred cannot
            if (pred->left == NULL)
                break;
            // If pred can, go down the left branch
            else    
                pred = pred->left;
        }
        else
            if (pred->right == NULL)
                break;
            else    
                pred = pred->right;

    }

    new->parent = pred;

    if (vertexKeyCompare(new, pred) == -1)
        pred->left = new;
    else
        pred->right = new;
}

int deleteFromTree(Tree t, char *word); // Deletes vertex with key, "word"
void setVertexList(Tree t, char *word, List urls); // Sets the urls list of a vertex

void showTree(Tree t) {
    /*
    width = number of spaces
    d = findDepth(t)
    q = newQueue()
    enQueue(q, t->root)
    curr_d = current depth
    print width d - curr_d times
    print q
    print new line

    while (q is not empty)
        sub_trees_printed = 0
        print width d - curr_d times
        while (sub_trees_printed != curr_d)
            pred = deQueue(q)
            print left
            print width * 2
            print right
            sub_trees_printed++
            enQueue left and right
        print new line
        curr_d++
    */

    char space[MAX_CHAR] = "               ";
    int depth = getDepth(t);
    int curr_depth = 0;
    VertexQueue q = newVertexQueue();

    enterVertexQueue(q, t->root);
    for (int i = 0; i < depth - curr_depth; i++) printf("%s", space);
    printf("%s", t->root->word);

    while (!emptyVertexQueue(q) && curr_depth <= depth) {
        int subTreesPrinted = 0;
        for (int i = 0; i < depth - curr_depth; i++) printf("%s", space);
        while (subTreesPrinted != curr_depth) {
            Vertex *pred = leaveVertexQueue(q);
            if (pred->left != NULL) {
                printf("%s", pred->left->word);
                enterVertexQueue(q, pred->left);
            }
            for (int i = 0; i < 2; i++) printf("%s", space);
            if (pred->right != NULL) {
                printf("%s ", pred->right->word);
                enterVertexQueue(q, pred->right);
            }
            subTreesPrinted++;
        }
        printf("\n\n");
        curr_depth++;
    }

    disposeVertexQueue(q);
}

int getDepth(Tree t) {
    // Zero indexed so subtract 1
    return findDepth(t->root) - 1;
}

static int findDepth(Vertex *root) {
    int maxLeftDepth = 0;
    int maxRightDepth = 0;
    if (root == NULL) return 0;
    
    maxLeftDepth = findDepth(root->left);
    maxRightDepth = findDepth(root->right);

    return (maxLeftDepth >= maxRightDepth) ? maxLeftDepth + 1 : maxRightDepth + 1;
}

// Return 1 if v1 > v2, 0 if v1 == v2/ -1 if v1 < v2
static int vertexKeyCompare(Vertex *v1, Vertex *v2) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (v1->word[i] == '\0' || v2->word[i] == '\0') break;
        if (v1->word[i] > v2->word[i]) return 1;
        else if (v1->word[i] < v2->word[i]) return -1;
    }
    return 0;
}

// Create a new Vertex for the tree
static Vertex *newVertex(char *str) {
    Vertex *v = malloc(sizeof(struct Vertex));
    v->left = NULL;
    v->right = NULL;
    v->parent = NULL;
    v->word = malloc(sizeof(char) * MAX_CHAR);
    v->urls = newList();

    strcpy(v->word, str);

    return v;
}