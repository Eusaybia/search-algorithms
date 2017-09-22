// Main file for Yaggle search engine
#include <stdio.h>
#include <stdlib.h>
#include "pagerank.h"
#include "readData.h"
#include "graph.h"
#include "searchPagerank.h"

int main(int argc, char* argv[]) {
    Queue collectionUrls = getCollectionUrls();
    Graph urlGraph = createUrlGraph(collectionUrls);

    printf("Welcome to Yaggle. Enter your query\n");
    pageRankWeights(0.85, 0.00001, 1000, urlGraph);
    return EXIT_SUCCESS;
}
