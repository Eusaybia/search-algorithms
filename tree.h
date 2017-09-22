// tree.h - Interface to binary search tree of with key value strings 
// Written by Kongwei Ying, September 2017

#include "list.h"

typedef struct TreeRep *Tree;

Tree newTree();
void dropTree(Tree t); // Frees the tree's associated memory
int insertIntoTree(Tree t, char *word); // Inserts vertex with key, "word" 
int deleteFromTree(Tree t, char *word); // Deletes vertex with key, "word"
void setVertexList(Tree t, char *word, List urls); // Sets the urls list of a vertex