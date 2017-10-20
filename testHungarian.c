#include <stdio.h>
#include <stdlib.h>
#include "hungarian.h"

int main() {

	h_problem p;

	// an example cost matrix

	double r[10][10] = {{ 1.00,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80 },
		{  1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.00,  0.20,  0.40 },
		{  0.80,  0.60,  0.60,  0.60,  0.60,  0.60,  0.60,  0.60,  0.80,  1.00 },
		{  2.30,  1.80,  1.50,  1.20,  1.10,  1.00,  1.30,  1.60,  1.90,  2.20 },
		{  0.60,  0.40,  0.20,  0.00,  0.20,  0.40,  0.60,  0.80,  1.00,  1.20 },
		{  1.80,  1.60,  1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.00 },
		{  1.60,  1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.20,  0.20 },
		{  0.70,  0.40,  0.30,  0.20,  0.50,  0.80,  1.10,  1.40,  1.70,  2.00 },
		{  1.70,  1.40,  1.10,  0.80,  0.50,  0.20,  0.30,  0.40,  0.70,  1.00 },
		{  0.60,  0.40,  0.40,  0.40,  0.40,  0.40,  0.60,  0.80,  1.00,  1.20 }};

	double** m = (double**)calloc(10,sizeof(double*));

	for (int i = 0; i < 10; i++) {
		m[i]= (double*)calloc(10,sizeof(double));

		for (int j = 0; j < 10; j++) m[i][j] =  r[i][j];

	}

	//initialise hungarian
	hungarian_init(&p, m , 10) ;

	printf("Cost Matrix:\n");
	//print cost matrix
	hungarian_print_costmatrix(&p);

	//solve
	printf("Cost: %lf\n", hungarian_solve(&p));

	//print assignment
	printf("Assignemnt:\n");
	hungarian_print_assignment(&p);

	hungarian_free(&p);

	return 0;
}
