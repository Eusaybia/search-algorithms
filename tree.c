// tree.h - Interface to binary search tree 
// Written by Kongwei Ying, September 2017

#include "tree.h"

typedef struct Vertex {
    struct Vertex *left;
    struct Vertex *right;
    struct Vertex *parent;
    char *word; // Acts as key
    List urls; // List of urls that contain this word
} Vertex;

typedef struct TreeRep {
   struct Vertex *root; 
} TreeRep;

static int keyCompare(char *str1, char *str2);
static int strToKey(char *str);

Tree newTree();
void dropTree(Tree t); // Frees the tree's associated memory
int insertIntoTree(Tree t, char *word); // Inserts vertex with key, "word" 
int deleteFromTree(Tree t, char *word); // Deletes vertex with key, "word"
void setVertexList(Tree t, char *word, List urls); // Sets the urls list of a vertex
static int keyCompare(char *str1, char *str2);
static int strToKey(char *str);