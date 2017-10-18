// Written by Dennis Gann, October 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"


typedef struct MatrixRep {
	int size;
	double **matrix;
	int **assignments;
    int *m_cols;    // 2D matrix
    int *m_rows;
} MatrixRep;


Matrix newMatrix(int size) {
	MatrixRep *m = (MatrixRep *)malloc(size * sizeof(MatrixRep));
	assert(m != NULL);

	// Initialise all members
	m->size = size;
    m->m_cols = (int *)malloc(size * sizeof(int));
    m->m_rows = (int *)malloc(size * sizeof(int));
	m->matrix = (double **)malloc(size * sizeof(double *));
	assert(m->matrix != NULL);
    m->assignments = (int **)malloc(size * sizeof(int *));
    assert(m->assignments != NULL);

	for (int i = 0; i < size; i++) {
        m->m_cols[i] = 0;
        m->m_rows[i] = 0;


		m->matrix[i] = (double *)malloc(size * sizeof(double));
		assert(m->matrix[i] != NULL);

        m->assignments[i] = (int *)malloc(size * sizeof(int));
        assert(m->assignments[i] != NULL);

        //initialise all values
        for (int j = 0; j < size; j++) {
            m->matrix[i][j] = 0.0;
            m->assignments[i][j] = -1;
        }
    }

	return m;
}

// Free all malloced memory associated with the matrix
void disposeMatrix(Matrix m) {
	for (int i = 0; i < m->size; i++) {
		free(m->matrix[i]);
	}
	free(m->matrix);
	free(m);
}

// Return: 1 if edge successfully added, 0 if unsuccessful
int addCost(Matrix m, int from, int to, double cost) {

	if (from < 0 || to < 0 || from >= m->size || to >= m->size) {
		printf("Index out of bounds\n");
		return 0;
	}

	// Add an cost
	m->matrix[from][to] = cost;
	return 1;
}

//Display matrix
void showMatrix(Matrix m) {
	assert(m != NULL);

    for (int i = 0; i < m->size; i++) {
        printf("[ ");
        for (int j= 0; j < m->size; j++) {
            printf("%.2lf ", m->matrix[i][j]);
        }
        printf("]\n");
    }
}

void showAssignments(Matrix m) {
	assert(m != NULL);

    for (int i = 0; i < m->size; i++) {
        printf("[ ");
        for (int j= 0; j < m->size; j++) {
            printf("%d ", m->assignments[i][j]);
        }
        printf("]\n");
    }
}


void subtractRowMin(Matrix m, int row) {
    if (row < 0 || row >= m->size) {
		printf("Index out of bounds\n");
		exit(EXIT_FAILURE);
    }

	double min = m->matrix[row][0]; //set to the first index of row
    for (int i = 0; i < m->size; i++) {
        if (m->matrix[row][i] < min) min = m->matrix[row][i];
    }

    //remove min from all row elements
    for (int i = 0; i < m->size; i++) {
        m->matrix[row][i] -= min;
    }

}

void subtractColMin(Matrix m, int col) {
    if (col < 0 || col >= m->size) {
		printf("Index out of bounds\n");
		exit(EXIT_FAILURE);
    }

	double min = m->matrix[0][col]; //set to the first index of row
    for (int i = 0; i < m->size; i++) {
        if (m->matrix[i][col] < min) min = m->matrix[i][col];
    }

    //remove min from all col elements
    for (int i = 0; i < m->size; i++) {
        m->matrix[i][col] -= min;
    }

}

int isAssignable(Matrix m) {
    //count 1's in assignments matrix
    //if equal to size then return 1

    assert(m != NULL);
    int count = 0;

    for (int i = 0; i < m->size; i++) {
        for (int j= 0; j < m->size; j++) {
            if (m->matrix[i][j] == 1) count++;
        }
    }
    if (count) return 1;
    else return 0;

}

void makeAssignments(Matrix m) {
    //go through each row and find first 0

    for (int i = 0; j < size; i++) {
        for (int j = 0; j < size; j++) {
            m->assignments[i][j] = -1;
        }
    }

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (m->matrix[row][col] == 0.0 && m->assignments[row][col] == -1) {

                for (int k = 0; k < size; k++) {
                    if (m->matrix[row][k] == 0.0) m->assignments[row][k] = 0;
                    if (m->matrix[k][col]) == 0.0) m->assignments[k][col] = 0;
                }
                m->assignments[row][col] = 1;
            }
        }
    }
}

void createMarks(Matrix m) {



}
