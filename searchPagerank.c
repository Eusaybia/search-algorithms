// searchPagerank.c : Main file for Pagerank
// Written by Konway Ying, September 2017
// Modified by Rahil Agrawal, Sept-Oct 2017

#include "colours.h"
#include "pagerank.h"
#include "readData.h"
#include "list.h"
#include "invertedIndex.h"
#include "graph.h"
#include "searchPagerank.h"


int main(int argc, char *argv[]) {
	// normalise the search term queries which are passed as
	// Command-line arguments
	char matchedUrlList[MAX_V][MAX_CHAR] = {{0}};
	char queries[MAX_QUERIES][MAX_CHAR] = {{0}};
	getQueries(argc, argv, queries);
	// Get the urls that satisfy the query terms sort them in groups
	// of the number of query terms satisfied
	int nQueries = findMatchedUrls(matchedUrlList, queries, argc - 1);
	// Apply pagerank algorithm on these URLs and write to stdout
	findPagerank(nQueries, matchedUrlList);
	return EXIT_SUCCESS;
}

// Finds urls from invertedIndex that contain query words
// Fills matchedUrlList with urls
// Returns number of queries entered
int findMatchedUrls(char matchedUrlList[MAX_V][MAX_CHAR], char queries[MAX_QUERIES][MAX_CHAR], int nQueries) {
	FILE *invertedIndexFp = fopen("invertedIndex.txt", "r");
	if (invertedIndexFp == NULL){
		perror("Error opening file");
		exit(1);
	}

	char buf[MAX_CHAR] = {0};
	int nMatchedUrls = 0;

	while (1){
		char invertedIndexStr[MAX_CHAR] = {0};
		// Scan every word of the invertedIndex
		if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == EOF)
			break;
		// If the query matches the word in the index, load the word's urls
		for (int i = 0; i < nQueries; i++){
			if (strcmp(invertedIndexStr, queries[i]) == 0){
				// Read the rest of the line into buf
				fgets(buf, MAX_CHAR, invertedIndexFp);
				// Then extract the strings and place them into matchedUrlList
				char *url = NULL;
				url = strtok(buf, " ");
				for (int j = nMatchedUrls; url != NULL && j < MAX_QUERIES; j++){
					// Remove non-char characters such as new lines from the string
					if (sscanf(url, "%s", url) == EOF) break;
					strcpy(matchedUrlList[j], url);
					nMatchedUrls++;
					url = strtok(NULL, " ");
				}
			}
		}
	}
	fclose(invertedIndexFp);
	return nQueries;
}

// Sorts matchedUrlList according to pagerankList
// Returns a string array of urls
void findPagerank(int nQueries, char matchedUrlList[MAX_V][MAX_CHAR]) {
	// An array of urls indexed by frequency of matching query words - 1
	List *queryTable = malloc(sizeof(List) * nQueries);
	for (int i = 0; i < nQueries; i++){
		queryTable[i] = newList();
	}
	// Querytable is indexed by the number of query terms satisfed - 1
	// Each position in the element is a list of urls that satisfy that
	// many query terms.
	for (int i = 0; *matchedUrlList[i]; i++){
		int count = 1;
		if (strcmp(matchedUrlList[i], "-1") == 0) continue;
		for (int j = 0; *matchedUrlList[j]; j++){
			if (i != j && strcmp(matchedUrlList[i], matchedUrlList[j]) == 0 && strcmp(matchedUrlList[j], "-1") != 0){
				strcpy(matchedUrlList[j], "-1");
				count++;
			}
		}
		if (count > 0)
			appendList(queryTable[count - 1], matchedUrlList[i], 0, 0);
	}
	int nResults = 30;
	for (int i = nQueries - 1; i >= 0; i--){
		// Sort the lists in descending order of pageranks
		sortList(queryTable[i], cmpPagerank);
		if (!isEmpty(queryTable[i]))
			// Print the top 30 pageranks to stdout
			showList(queryTable[i], stdout, '\n', &nResults);
	}

	// Free queryTable
	for (int i = 0; i < nQueries; i++){
		dropList(queryTable[i]);
	}
	free(queryTable);
}
