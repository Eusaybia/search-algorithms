#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char* argv[]) {
	int size = 5;
	Matrix m = newMatrix(size);
    addCost(m, 0, 0, 1.5);
    addCost(m, 0, 1, 1.4);
    addCost(m, 0, 2, 1.3);
    addCost(m, 0, 3, 0.7);
    addCost(m, 0, 4, 123);
    addCost(m, 1, 2, 1.5);
    addCost(m, 3, 0, 1.5);
	showMatrix(m);
    printf("+++++++++++++++++++\n");
    subtractRowMin(m, 0);
    subtractColMin(m, 2);
    showMatrix(m);
	disposeMatrix(m);
	return EXIT_SUCCESS;
}
