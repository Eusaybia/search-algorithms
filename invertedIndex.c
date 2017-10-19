// invertedIndex.c - Generate an inverted index of words from urls
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, Sept-Oct 2017
#include "invertedIndex.h"

int main(int argc, char* argv[]){
    Queue collectionUrls2 = getCollectionUrls();
    getInvertedIndex(collectionUrls2);
    return EXIT_SUCCESS;
}
// Very similar logic to createUrlGraph() in readData.c
Tree getInvertedIndex(Queue collectionUrls) {
    Tree t = newTree();
    // e.g. url31
    char url_from[MAX_CHAR] = {0};
    while (!emptyQueue(collectionUrls)) {
        strcpy(url_from, leaveQueue(collectionUrls));
        char url_from_location[MAX_CHAR] = {0};
        strcat(url_from_location, url_from);
        strcat(url_from_location, ".txt");
        FILE *nextUrlFp = fopen(url_from_location, "r");
        // We want to look for urls and ignore all other strings
        char curr_word[MAX_CHAR] = {0};
        while (1) {
            // If we reach the end of the file
            if (fscanf(nextUrlFp, "%s", curr_word) == EOF) {
                break;
            }

            if (strcmp(curr_word, "#start") == 0) continue;
            // Skip words with first 7 letters "Section"
            else if (strncmp(curr_word, "Section", 7) == 0) continue;
            // Skip words with first 3 letters "url"
            else if (strncmp(curr_word, "url", 3) == 0) continue;
            else if (strcmp(curr_word, "#end") == 0) continue;

            // Convert word to lower case and remove full stops
            normalize(curr_word);
            // If not in the tree, adds vertex curr_word to the tree
            insertIntoTree(t, curr_word);
            // Adds or updates the list urls within the vertex curr_word
            addUrl(t, curr_word, url_from);
        }
        fclose(nextUrlFp);
    }
    FILE *invertedIndexFp = fopen("invertedIndex.txt", "w");
	if (invertedIndexFp == NULL) {
        perror("Error, could not open file");
	}
    else {
        showInOrder(t, invertedIndexFp);
        fclose(invertedIndexFp);
    }
    return t;
}
