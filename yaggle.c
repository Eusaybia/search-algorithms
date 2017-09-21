// Main file for Yaggle search engine
#include <stdio.h>
#include <stdlib.h>
#include "pagerank.h"
#include "readData.h"
#include "searchPagerank.h"

int main(int argc, char* argv[]) {
    Queue collectionUrls = getCollectionUrls();
    Graph urlGraph = createUrlGraph(collectionUrls);

    printf("Welcome to Yaggle. Enter your query\n");
    return EXIT_SUCCESS;
}