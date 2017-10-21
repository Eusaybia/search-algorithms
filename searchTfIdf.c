/*
    searchTfIdf.c : Main file for searchtfidf


    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */


#include "searchTfIdf.h"

int main(int argc, char *argv[]) {

	//check args provided are ok
	if (!argsOk(argc, argv)) return EXIT_FAILURE;

	//get query terms from command line args
	char queries[MAX_QUERIES][MAX_CHAR] = {{0}};
	int nQueries = getQueries(argc, argv, queries);

	//open invertedIndex.txt file stream
	FILE *invertedIndexFp = fopen("invertedIndex.txt", "r");
	if (invertedIndexFp == NULL){
		perror("Error opening file");
		exit(1);
	}

	//total no of docs/urls in collection.txt
	int totalDocs = getTotalDocs("collection.txt");

	//create new urlList to store details for each url
	List urlList = newList();

	//initialise line buffer
	char buf[MAX_CHAR] = {0};

	while (1){

		//initialise string to store words of invertedIndex
		char invertedIndexStr[MAX_CHAR] = {0};

		//scan every word of the invertedIndex
		if (fscanf(invertedIndexFp, "%s", invertedIndexStr) == EOF)
			break;

		//if the query matches the word in the index, load the word's urls
		char matchedUrlList[MAX_V][MAX_CHAR] = {{0}};
		int nMatchedUrls = 0;

		//loop through all query terms provided
		for (int i = 0; i < nQueries; i++){

			//if the curr word in the invertedIndex matches one of the queries
			if (strcmp(invertedIndexStr, queries[i]) == 0){
				//scanned word matches one of query terms

				//Read the rest of the line into buf
				memset(buf, 0, MAX_CHAR);
				fgets(buf, MAX_CHAR, invertedIndexFp);

				//Then extract the strings and place them into matchedUrlList
				char *url = NULL;
				url = strtok(buf, " ");
				for (int j = 0; url != NULL && j < MAX_V; j++){
					if (sscanf(url, "%s", url) == EOF) break;
					//copy url into matchedUrlList
					strcpy(matchedUrlList[j], url);
					//increment no of matched urls
					nMatchedUrls++;
					url = strtok(NULL, " ");
				}

				//loop through each url we matched above (matchedUrlList)
				for (int j = 0; j < nMatchedUrls; j++){

					//determin urlFileLocation
					char urlFileLocation[MAX_CHAR] = {0};
					strcat(urlFileLocation, matchedUrlList[j]);
					strcat(urlFileLocation, ".txt");
					FILE *urlToOpen = fopen(urlFileLocation, "r");

					//get tfidf value for urlToOpen stream, and current query term
					double tfidf = getTfIdf(queries[i], urlToOpen, nMatchedUrls, totalDocs);
					//add tfIdf value for url to urlList
					addTfIdf(urlList, matchedUrlList[j], tfidf, 1);

					fclose(urlToOpen);

				}
			}
		}
	}

	//close invertedIndex file stream
	fclose(invertedIndexFp);
	//show the top 30 pages based on tf-idf
	showTfIdfList(urlList, stdout, 30);
	//delete the urlList
	dropList(urlList);

	return EXIT_SUCCESS;
}

//Calculates the tfidf value for a given term in a fileStream doc
double getTfIdf(char term[MAX_CHAR], FILE *doc, int totalMatchedUrls, int totalDocs) {

	//declare and initialise variables
	int docLength = 0;	//length of document (word count)
	int tc = 0;	//term count (no. of term occurences)
	double tf = 0;	//term frequency (tc/docLength)
	double idf  = 0;//inverse document freq. (log10(totalDocs/totalMatchedUrls))
	double tfidf = 0;	//tf-idf (tf * idf)

	//initialise string to store current scanned word of doc file stream
	char currWord[MAX_CHAR] = {0};

	//flag to mark that we are past section 1 ie. in the body/text (Section 2)
	int pastSec1 = 0;

	//get all words in file stream doc until EOF
	while (fscanf(doc, "%s", currWord) != EOF){

		if (strcmp(currWord, "#start") == 0){
			//skip next word which will be Section-1/2
			fscanf(doc, "%s", currWord);
			continue;
		}
		// Skip words with first 3 letters "url"
		else if (strcmp(currWord, "#end") == 0){
			//skip next word which will be Section-1/2
			fscanf(doc, "%s", currWord);
			pastSec1 = 1;
			continue;
		}
		else if (!pastSec1) continue;

		//normalise the current word
		normalise(currWord);

		//if curr word matches term, increment term count
		if (strcmp(currWord, term) == 0)
			tc++;

		//for each word in Section 2 increment doc length (word count)
		docLength++;

	}

	//perform calculations for variables declared above
	tf = (double)tc / docLength;
	idf = log10((double)totalDocs / totalMatchedUrls);
	tfidf = tf * idf;

	//return calculated tfidf value
	return tfidf;

}

//gets the total number of docs in supplied collection (filePath)
int getTotalDocs(char *filePath) {
	//open collection filePath stream
	FILE *collectionFp = fopen(filePath, "r");
	assert(collectionFp != NULL);
	char str[MAX_CHAR] = {0};
	int totalDocs = 0;
	//count number of strings (ie. docs/urls)
	while (fscanf(collectionFp, "%s", str) != EOF){
		totalDocs++;
	}
	fclose(collectionFp);
	return totalDocs;

}

//checks correct number of commandline arguments are given
int argsOk(int argc, char *argv[]) {
	if (argc == 1){
		printf("Usage: ./searchTfIdf query-term(s) ...\n");
		return 0;
	}
	else
		return 1;
}
