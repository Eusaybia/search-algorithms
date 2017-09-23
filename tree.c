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
static void print_t(Vertex *tree);
int _print_t(Vertex *tree, int is_left, int offset, int depth, char s[20][255]);
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

// This function has a print depth limitation of 20 lines
// Try changing the magic number 20 in the print_t and _print_t functions
// if you need to increase the depth it prints up to
void showTree(Tree t) {
    print_t(t->root);
}

// Taken from here
// https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
static void print_t(Vertex *tree) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

// Taken from here
// https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
int _print_t(Vertex *tree, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%s)", tree->word);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
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