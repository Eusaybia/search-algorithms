// invertedIndex.c - Generate an inverted index of words from urls
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, September 2017
#include "invertedIndex.h"

// Very similar logic to createUrlGraph() in readData.c
Tree getInvertedIndex(Queue collectionUrls) {
    Tree t = newTree();
    // e.g. url31
    char url_from[MAX_CHAR] = {0};
    char subdir[MAX_CHAR] = "./Sample1/";
    while (!emptyQueue(collectionUrls)) {
        strcpy(url_from, leaveQueue(collectionUrls));
        char url_from_location[MAX_CHAR] = {0};
        // e.g. ./Sample1/
        strcpy(url_from_location, subdir);
        // e.g. ./Sample1/url31
        strcat(url_from_location, url_from);
        // e.g. ./Sample1/url31.txt
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
            // for (int i = 0; curr_word[i] != '\0'; i++) {
            //     curr_word[i] = tolower((unsigned char)curr_word[i]);
            //     if (curr_word[i] == '.') curr_word[i] = '\0';
            // }
            normalize(curr_word);
            // If not in the tree, adds vertex curr_word to the tree
            insertIntoTree(t, curr_word);
            // Adds or updates the list urls within the vertex curr_word
            addUrl(t, curr_word, url_from);
        }
    }
    FILE *invertedIndexFp = fopen("invertedIndex.txt", "w");
	if (invertedIndexFp == NULL) {
        perror("Error, could not open file");
	}
    else {
        showInOrder(t, invertedIndexFp);
        fclose(invertedIndexFp);
    }
    //showInOrder(t, stdout);
    return t;
}
