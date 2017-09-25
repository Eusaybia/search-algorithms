// testList.c - File to test functionality of list ADT
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char* argv[]) {
    List l = newList();
    appendList(l, "carrot");
    appendList(l, "durian");
    appendList(l, "fruit");
    appendList(l, "grape");
    appendList(l, "ham");
    appendList(l, "eggplant");
    appendList(l, "apple");
    appendList(l, "banana");
    appendList(l, "banana");
    appendList(l, "banana");
    printf("Unsorted List: ");
    showList(l, stdout);
    sortList(l);
    printf("Sorted List: ");
    showList(l, stdout);
    dropList(l);
    return EXIT_SUCCESS;
}