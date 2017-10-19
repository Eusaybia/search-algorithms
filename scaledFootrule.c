// Brute force scaled footrule
// Written by Kongwei Ying

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N_ROWS 100
#define MAX_CHAR 256

int argsOk(int argc, char *argv[]);
void readRankFile(char *filename, int *array, int *maxRows);
int factorial(int n);
void swap (int v[], int i, int j);
void perm (int v[], int n, int i, int *permArrays, int *permNum);

int main(int argc, char *argv[]) {
    // A 2d array to hold different ranking list rankings
    int **rankArrays = NULL;
    int maxRows = 0; // Determined by the no. entries in a rank file
    assert(argsOk(argc, argv));

    // Create columns
    rankArrays = malloc(sizeof(int *) * (argc - 1));
    // Determine the maximum number of rows based on max size
    // But for now, just create a shit ton of rows
    for (int i = 0; i < (argc - 1); i++) {
        rankArrays[i] = malloc(sizeof(int) * N_ROWS);
        readRankFile(argv[i + 1], rankArrays[i], &maxRows);
        printf("maxrows = %d\n", maxRows);
    }
    
    int nPerms = factorial(maxRows);

    // Create a perms array to hold all the combinations of url positions
    // Create n! columns (each column representing a perm) with maxRows
    // number of rows (each row representing a url's position for that perm)
    // This is a 2d array represented as a 1d array
    int *permArrays = malloc(sizeof(int[nPerms][maxRows]));
    
    // Create an array of sorted numbers to create perms from
    int *permNums = malloc(sizeof(int) * maxRows);
    for (int i = 1; i <= maxRows; i++) permNums[i - 1] = i;
    
    // Populate permArrays with all possible permutations
    int permNum = 0;
    perm(permNums, maxRows, 0, permArrays, &permNum);
    
    // Print the permArrays for testing
    // for (int i = 0; i < nPerms; i++) {
    //     printf("Perm %d:\n", i);
    //     for (int j = 0; j < maxRows; j++) {
    //         printf("%d ", permArrays[i * maxRows + j]);
    //     }
    //     printf("\n");
    // }

    return EXIT_SUCCESS;
}

// Calculate factorial
int factorial(int n) {
    if (n == 1) return 1;
    return n * factorial(n - 1);
}

//http://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture25.html
/* function to swap array elements */

void swap (int v[], int i, int j) {
	int	t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}

/* recursive function to generate permutations */
void perm (int v[], int n, int i, int *permArrays, int *permNum) {

	/* this function generates the permutations of the array
	 * from element i to element n-1
	 */
	int	j;

	/* if we are at the end of the array, we have one permutation
	 * we can use (here we print it; you could as easily hand the
	 * array off to some other function that uses it for something
	 */
	if (i == n) {
        for (j=0; j<n; j++) {
            printf ("%d ", v[j]);
            permArrays[(*permNum) * n + j] = v[j];
        }
        (*permNum)++;
        printf ("\n");
	} else
		/* recursively explore the permutations starting
		 * at index i going through index n-1
		 */
		for (j=i; j<n; j++) {

			/* try the array with i and j switched */

			swap (v, i, j);
			perm (v, n, i+1, permArrays, permNum);

			/* swap them back the way they were */

			swap (v, i, j);
		}
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
        numRows = i++;
        if (fscanf(fp, "url%d\n", &array[i]) == EOF) break;
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