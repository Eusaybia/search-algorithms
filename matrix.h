// matrix.h ... interface to handle matrix
// Written by Dennis Gann, October 2017

#ifndef MATRIX_H
#define MATRIX_H

typedef struct MatrixRep *Matrix;

// Function signatures

Matrix newMatrix(int size);
void disposeMatrix(Matrix m);
int addCost(Matrix m, int from, int to, double cost);
void subtractRowMin(Matrix m, int row);
void subtractColMin(Matrix m, int col);
void showMatrix(Matrix m);
void showAssignments(Matrix m);


int isAssignable(Matrix m);
void makeAssignments(Matrix m);
void createMarks(Matrix m);

#endif
