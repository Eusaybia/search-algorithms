// invertedIndex.c - Generate an inverted index of words from urls
// Written by Kongwei Ying, September 2017
// Modified by Rahil Agrawal, Sept-Oct 2017
#include "invertedIndex.h"

int main(int argc, char *argv[]) {
	Queue collectionUrls = getCollectionUrls();
	getInvertedIndex(collectionUrls);
	disposeQueue(collectionUrls);
	return EXIT_SUCCESS;
}

// Generate InvertedIndex BST from URLs
Tree getInvertedIndex(Queue collectionUrls) {
	Tree t = newTree();
	int readWords = 0;
	char *urlFrom;
	char urlFromLocation[MAX_CHAR] = {0};
	char currWord[MAX_CHAR] = {0};
	while (!emptyQueue(collectionUrls)){
		urlFrom = leaveQueue(collectionUrls);
		strcpy(urlFromLocation, urlFrom);
		strcat(urlFromLocation, ".txt");
		FILE *nextUrlFp = fopen(urlFromLocation, "r");
		if (nextUrlFp == NULL){
			fprintf(stderr, "Couldn't open %s\n", urlFrom);
			continue;
		}
		readWords = 0;
		while (fscanf(nextUrlFp, "%s", currWord) != EOF){
			// Only look for words in Section-2
			if (strcmp(currWord, "#start") == 0){
				fscanf(nextUrlFp, "%s", currWord);
				continue;
			}
			else if (strcmp(currWord, "#end") == 0){
				fscanf(nextUrlFp, "%s", currWord);
				readWords = 1;
				continue;
			}
			else if (readWords == 0) continue;

			// Strip words of punctuation
			normalise(currWord);
			// Adds currWord to the tree
			insertIntoTree(t, currWord);
			// Adds the urlFrom into the list of urls for currWord
			addUrl(t, currWord, urlFrom);
		}
		free(urlFrom);
		fclose(nextUrlFp);
	}
	FILE *invertedIndexFp = fopen("invertedIndex.txt", "w");
	if (invertedIndexFp == NULL){
		printf("Error, could not open file");
	}
	else {
		// Print the inverted index tree into invertedIndex.txt
		printInOrder(t, invertedIndexFp);
		fclose(invertedIndexFp);
	}
	dropTree(t);
	return t;
}
