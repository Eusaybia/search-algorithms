// searchTfIdf.c : Main file for searchtfidf
// Written by Dennis Gann, October 2017
// Modified by Rahil Agrawal, October 2017

#include "searchTfIdf.h"
#include "colours.h"
#include "pagerank.h"
#include "readData.h"
#include "list.h"
#include "invertedIndex.h"
#include "graph.h"
#include "searchFunctions.h"

int main(int argc, char *argv[]) {
	//GET QUERIES FROM COMMAND LINE ARGS
	char queries[MAX_QUERIES][MAX_CHAR] = {{0}} ;
	int nQueries = argc - 1 ;
	if (nQueries == 0){
		perror("Please supply search terms") ;
		exit(1) ;
	}

	getQueries(argc, argv, queries) ;

	//open invertedIndex file stream

	FILE *invertedIndexFp = fopen("invertedIndex.txt", "r") ;
	if (invertedIndexFp == NULL){
		perror("Error opening file") ;
		exit(1) ;
	}

	int totalDocs = getTotalDocs("./collection.txt") ;
	List urlList = newList() ;
	char buf[MAX_CHAR] = {0} ;

	while (1){
		char invertedIndexStr[MAX_CHAR] = {0} ;

		// Scan every word of the invertedIndex
		if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == EOF)
			break ;

		// If the query matches the word in the index, load the word's urls
		char matchedUrlList[MAX_V][MAX_CHAR] = {{0}} ;
		int nMatchedUrls = 0 ;

		for (int i = 0 ; i < nQueries ; i++){
			if (strcmp(invertedIndexStr, queries[i]) == 0){
				//scanned word matches one of query terms

				// Read the rest of the line into buf
				memset(buf, 0, MAX_CHAR) ;
				fgets(buf, MAX_CHAR, invertedIndexFp) ;
				// Then extract the strings and place them into matchedUrlList
				char *url = NULL ;
				url = strtok(buf, " ") ;
				for (int j = 0 ; url != NULL && j < MAX_QUERIES ; j++){
					// Remove non-char characters such as new lines from the string
					if (sscanf(url, "%s", url) == EOF) break ;
					strcpy(matchedUrlList[j], url) ;
					nMatchedUrls++ ;
					url = strtok(NULL, " ") ;
				}

				for (int j = 0 ; j < nMatchedUrls ; j++){

					char url_from_location[MAX_CHAR] = {0} ;
					strcat(url_from_location, matchedUrlList[j]) ;
					strcat(url_from_location, ".txt") ;
					FILE *urlToOpen = fopen(url_from_location, "r") ;

					double tfidf = getTfIdf(queries[i], urlToOpen, nMatchedUrls, totalDocs) ;
					addTfIdf(urlList, matchedUrlList[j], tfidf, 1) ;

					fclose(urlToOpen) ;

				}
			}
		}
	}

	fclose(invertedIndexFp) ;
	showTfIdfList(urlList, stdout, 30) ;
	dropList(urlList) ;
	return EXIT_SUCCESS ;
}

double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs) {

	//declare and initialise variables
	int docLength = 0 ;
	int tc = 0 ;
	double tf = 0 ;
	double idf  = 0 ;
	double tfidf = 0 ;

	char curr_word[MAX_CHAR] = {0} ;

	while (1){
		// If we reach the end of the file
		if (fscanf(doc, "%s", curr_word) == EOF){
			break ;
		}

		if (strcmp(curr_word, "#start") == 0){
			fscanf(doc, "%s", curr_word) ;
			continue ;
		}
		// Skip words with first 3 letters "url"
		else if (strncmp(curr_word, "url", 3) == 0) continue ;
		else if (strcmp(curr_word, "#end") == 0){
			fscanf(doc, "%s", curr_word) ;
			continue ;
		}

		normalize(curr_word) ;

		if (strcmp(curr_word, term) == 0){
			tc++ ;
		}

		docLength++ ;

	}

	tf = (double)tc / docLength ;
	idf = log10((double)totalDocs / totalMatchedUrls) ;
	tfidf = tf * idf ;

	return tfidf ;

}

//usage e.g. getTotalDocs("./Sample1/collection.txt")
int getTotalDocs(char *filePath) {

	FILE *collectionFp = fopen(filePath, "r") ;
	assert(collectionFp != NULL) ;
	char str[MAX_CHAR] = {0} ;
	int totalDocs = 0 ;
	while (fscanf(collectionFp, "%s", str) != EOF){
		totalDocs++ ;
	}
	fclose(collectionFp) ;
	return totalDocs ;

}
