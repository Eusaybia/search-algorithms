// testList.c - File to test functionality of list ADT
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char* argv[]) {
    List l = newList();
    appendList(l, "carrot", 0, 0);
    appendList(l, "durian", 0, 0);
    appendList(l, "fruit", 0, 0);
    appendList(l, "grape", 0, 0);
    appendList(l, "ham", 0, 0);
    appendList(l, "eggplant", 0, 0);
    appendList(l, "apple", 0, 0);
    appendList(l, "banana", 0, 0);
    appendList(l, "banana", 0, 0);
    appendList(l, "banana", 0, 0);

    printf("Unsorted List: ");
    int nNodes = ALL_NODES;
    showList(l, stdout, ' ', &nNodes);
    sortList(l, cmpStr);
    printf("Sorted List: ");
    showList(l, stdout, ' ', &nNodes);
    dropList(l);
    return EXIT_SUCCESS;
}
