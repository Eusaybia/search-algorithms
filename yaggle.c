// Main file for Yaggle search engine
#include <stdio.h>
#include <stdlib.h>
#include "colours.h"
#include "invertedIndex.h"
#include "pagerank.h"
#include "readData.h"
#include "graph.h"
#include "searchPagerank.h"

#define MAX_CHAR 256

void printImage(char *directory);

int main(int argc, char* argv[]) {
    printImage("yaggleImage.txt");
    printf(RED "\n\n               Welcome to Yaggle. Enter your query.\n" RESET);
    Queue collectionUrls1 = getCollectionUrls();
    Graph urlGraph = createUrlGraph(collectionUrls1);
    Queue collectionUrls2 = getCollectionUrls();
    getInvertedIndex(collectionUrls2);
    pageRankWeights(0.85, 0.00001, 1000, urlGraph);
    return EXIT_SUCCESS;
}

// Prints ASCII art!
// https://cboard.cprogramming.com/cplusplus-programming/161868-how-use-ascii-art-c-cplusplus.html
void printImage(char *directory) {
    char filename[MAX_CHAR];
    strcpy(filename, directory);
    FILE *fptr = NULL;
 
    if ((fptr = fopen(filename,"r")) == NULL) {
        fprintf(stderr,"error opening %s\n",filename);
        return;
    }

    char read_string[MAX_CHAR];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf(CYN "%s" RESET,read_string);

    printf("\n");
}