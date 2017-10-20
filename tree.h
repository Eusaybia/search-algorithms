// tree.h - Interface to binary search tree of with key value strings
// Written by Kongwei Ying, September 2017

#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "headers.h"
typedef struct TreeRep *Tree;

typedef struct Vertex {
    struct Vertex *left;
    struct Vertex *right;
    struct Vertex *parent;
    char *word; // Acts as key
    List urls; // List of urls that contain this word
} Vertex;

Tree newTree();
void dropTree(Tree t); // Frees the tree's associated memory
void insertIntoTree(Tree t, char *word); // Inserts vertex with key, "word"
void addUrl(Tree t, char *word, char *url); // Adds a url to the list inside the vertex with key word
void printInOrder(Tree t, FILE *fp); // Either prints to a file, or can print to std streams
void showTree(Tree t);
int getDepth(Tree t);

#endif
