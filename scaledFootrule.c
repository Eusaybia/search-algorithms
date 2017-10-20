// Scaled footrule main
// Written by Kongwei Ying, September 2017

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "scaledFootrule.h"
#include "hungarian.h"

int main(int argc, char *argv[]) {
    // A 2d array to hold different ranking list rankings
    int rankArrays[MAX_LISTS][N_ROWS] = {0};
    int maxRows = 0; // Determined by the no. entries in a rank file
    assert(argsOk(argc, argv));

    for (int i = 0; i < (argc - 1); i++) {
        readRankFile(argv[i + 1], rankArrays[i], &maxRows);
        // for (int j = 0; j < maxRows; j++) {
        //     printf("%d ", rankArrays[i][j]);
        // }
        // printf("maxrows = %d\n", maxRows);
    }
    
    // Set of urls, a union of all the lists
    int urlSet[MAX_LISTS * N_ROWS] = {0};
    int nElems = 0;
    for (int i = 0; i < (argc - 1); i++) {
        for (int j = 0; j < maxRows; j++) {
            insertSetArray(urlSet, &nElems, MAX_LISTS * N_ROWS, rankArrays[i][j]);
        }
    }
    
    // Sort set
    qsort(urlSet, nElems, sizeof(int), cmpInt);

    // Print set
    // printf("Set of urls:\n")
    // for (int i = 0; i < nElems; i++) {
    //     printf("%d ", urlSet[i]);
    // }
    // printf("\n");
    
    double **costMatrix = (double **)calloc(nElems, sizeof(double *));
	for (int i = 0; i < nElems; i++) {
		costMatrix[i] = (double*)calloc(nElems, sizeof(double));
    }
    // For each url
    for (int y = 0; y < nElems; y++) {
        // For each position of that url
        for (int x = 0; x < nElems; x++) {
            // For each list
            for (int i = 0; i < (argc - 1); i++) {
                int tc = findUrlPositionInRankList(rankArrays[i], urlSet[y], nElems);
                int ti = findRankListSize(rankArrays[i], nElems);
                // printf("url %d is rank %d in ranklist %d which has size %d\n", y, tc, i, ti);
                costMatrix[y][x] += scaledFootruleDistance(rankArrays, nElems, x + 1, tc, ti);
            }
            // printf("%.2lf ", costMatrix[y][x]);
        }
        // printf("\n");
    }

	//initialise hungarian
	h_problem p = hungarian_init(costMatrix, nElems);

	//print cost matrix
	// hungarian_print_costmatrix(p);

	//solve
	printf("%.6lf\n", hungarian_solve(p));

	//print assignment
	// printf("Assignment:\n");
    // hungarian_print_assignment(p);
    
    for (int i = 0; i < nElems; i++) {
        printf("url%d\n", urlSet[hungarian_url_from_rank(p, i, nElems)]);
    }

    hungarian_free(p);
    
    // Need to free my costMatrix array too
    
    return EXIT_SUCCESS;
}

// Reads the rank list into an array
void readRankFile(char *filename, int *array, int *maxRows) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File opening failed\n");
        exit(1);
    }
    int numRows = 0;
    int i = 0;
    while (1) {
        numRows = i;
        if (fscanf(fp, "url%d\n", &array[i]) == EOF) break;
        i++;
    }
    fclose(fp);
    if (numRows > *maxRows) {
        *maxRows = numRows;
    }
}

void insertSetArray(int *array, int *nElems, int size, int elem) {
    for (int i = 0; i < size; i++) {
        if (array[i] == elem) return;
    }
    array[*nElems] = elem;
    (*nElems)++;
}

int cmpInt(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
 }

// Checks if correct number of commandline arguments are given
int argsOk(int argc, char *argv[]) {
    if (argc == 1 || argc == 2) {
        printf("Usage: ./scaledFootrule file1 file2\n");
        return 0;
    }
    else
        return 1;
}

int findRankListSize(int rankArray[], int maxUrls) {
    int i;
    for (i = 0; i < maxUrls; i++) {
        if (rankArray[i] == 0) break;
    }
    return i;
}

int findUrlPositionInRankList(int rankArray[], int url, int maxUrls) {
    int i;
    for (i = 0; i < maxUrls; i++) {
        // This means there's no such url in this rankArray
        if (rankArray[i] == 0) return 0;
        if (url == rankArray[i]) break;
    }
    return i + 1;
}

double scaledFootruleDistance(int rankArrays[MAX_LISTS][N_ROWS], int n, int p, int tc, int ti) {
    double sfd = 0.0;
    if (tc == 0) return sfd;
    if (ti == 0 || n == 0) printf("NAN\n");
    sfd = fabs(((double)tc / (double)ti) - ((double)p / (double)n));
    return sfd;
}