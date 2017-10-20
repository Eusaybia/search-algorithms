#ifndef HUNGARIAN_H
#define HUNGARIAN_H

typedef struct {
	int size;
	double** cost;
	int** assignment;
} h_problem;

//initialise hungarian problem
void hungarian_init(h_problem* p, double** cost_matrix, int size);

//free memory allocated by init
void hungarian_free(h_problem* p);

//solve hungarian problem
double hungarian_solve(h_problem* p);

//print assignment
void hungarian_print_assignment(h_problem* p);

//print cost matrix
void hungarian_print_costmatrix(h_problem* p);

#endif
