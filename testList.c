// testList.c - File to test functionality of list ADT
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char* argv[]) {
    List l = newList();
    appendList(l, "lol");
    appendList(l, "mate");
    appendList(l, "mate");
    appendList(l, "mate");
    appendList(l, "mate");
    appendList(l, "mate");
    appendList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "lol");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    deleteFromList(l, "mate");
    showList(l);
    dropList(l);
    return EXIT_SUCCESS;
}