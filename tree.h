// tree.h - Interface to binary search tree of with key value strings 
// Written by Kongwei Ying, September 2017

#ifndef TREE_H
#define TREE_H

#include "list.h"

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
int deleteFromTree(Tree t, char *word); // Deletes vertex with key, "word"
void setVertexList(Tree t, char *word, List urls); // Sets the urls list of a vertex
void showTree(Tree t);
int getDepth(Tree t);

#endif 