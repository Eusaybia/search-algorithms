// testTree.c - Test file for Binary Search Tree

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main (int argc, char *argv[]) {
    Tree t = newTree();
    insertIntoTree(t, "banana");
    insertIntoTree(t, "carrot");
    insertIntoTree(t, "apple");
    insertIntoTree(t, "aadvark");
    insertIntoTree(t, "avalanche");
    insertIntoTree(t, "car");
    insertIntoTree(t, "cake");
    insertIntoTree(t, "cache");
    insertIntoTree(t, "carrie");
    showTree(t);
    addUrl(t, "banana", "url121");
    addUrl(t, "apple", "url121");
    addUrl(t, "carrot", "url131");
    addUrl(t, "car", "url141");
    addUrl(t, "cake", "url141");
    addUrl(t, "aadvark", "url141");
    showInOrder(t);
    //dropTree(t);
    return EXIT_SUCCESS;
}