// Brute force scaled footrule
// Written by Kongwei Ying

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define N_ROWS 100
#define MAX_LISTS 100
#define MAX_CHAR 256

int argsOk(int argc, char *argv[]);
void readRankFile(char *filename, int *array, int *maxRows);
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
    
    double *costMatrix = calloc(sizeof(double), maxRows * maxRows);
    // For each url
    for (int y = 1; y <= maxRows; y++) {
        // For each position of that url
        for (int x = 1; x <= maxRows; x++) {
            // For each list
            for (int i = 0; i < (argc - 1); i++) {
                int tc = findUrlPositionInRankList(rankArrays[i], y, maxRows);
                int ti = findRankListSize(rankArrays[i], maxRows);
                // printf("url %d is rank %d in ranklist %d which has size %d\n", y, tc, i, ti);
                costMatrix[y * maxRows + x] += scaledFootruleDistance(rankArrays, maxRows, x, tc, ti);
                // printf("%d: %.2lf|", i + 1, costMatrix[y * maxRows + x]);
            }
            printf("%.2lf ", costMatrix[y * maxRows + x]);
        }
        printf("\n");
    }
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
    printf("\n");
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