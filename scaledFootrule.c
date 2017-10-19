// Brute force scaled footrule
// Written by Kongwei Ying

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N_ROWS 100

int argsOk(int argc, char *argv[]);
int *readRankFile(char *file, int *array);

int main(int argc, char *argv[]) {
    // A 2d array to hold different ranking list rankings
    int **rankArrays = NULL;
    assert(argsOk(argc, argv));

    // Create columns
    rankArrays = malloc(sizeof(int *) * (argc - 1));
    // Determine the maximum number of rows based on max size
    // But for now, just create a shit ton of rows
    for (int i = 0; i < (argc - 1); i++) {
        rankArrays[i] = malloc(sizeof(int) * N_ROWS);
        readRankFile(argv[i + 1], rankArrays[i]);
    }

    return EXIT_SUCCESS;
}

void readRankFile(char *filename, int *array) {
    FILE *fp = fopen(filename, "r");
    for (int i = 0; ; i++)
        if (fscanf("%d", array));
    fclose(fp);
}

// Checks if correct number of commandline arguments are given
int argsOk(int argc, char *argv[]) {
    if (argc == 1 || argc == 2) {
        printf("Usage%% scaledFootrule   rankA.txt  rankD.txt");
        return 0;
    }
    else
        return 1;
}