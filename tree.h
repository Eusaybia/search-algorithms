/*
    tree.h - Interface to binary search tree of with key vaue strings

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */

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
int getDepth(Tree t);

#endif
