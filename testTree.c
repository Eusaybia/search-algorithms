// testTree.c - Test file for Binary Search Tree

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main (int argc, char *argv[]) {
    Tree t = newTree();
    /*
    insertIntoTree(t, "banana");
    insertIntoTree(t, "carrot");
    insertIntoTree(t, "apple");
    insertIntoTree(t, "aadvark");
    insertIntoTree(t, "avalanche");
    insertIntoTree(t, "car");
    insertIntoTree(t, "cake");
    insertIntoTree(t, "cache");
    */
    insertIntoTree(t, "c");
    insertIntoTree(t, "b");
    insertIntoTree(t, "a");
    insertIntoTree(t, "d");
    insertIntoTree(t, "f");
    insertIntoTree(t, "e");
    showTree(t);
    //dropTree(t);
    return EXIT_SUCCESS;
}