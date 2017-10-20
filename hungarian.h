#ifndef HUNGARIAN_H
#define HUNGARIAN_H

typedef struct h_problem_rep *h_problem;


//initialise hungarian problem
h_problem hungarian_init(double** cost_matrix, int size);

//free memory allocated by init
void hungarian_free(h_problem p);

//solve hungarian problem
double hungarian_solve(h_problem p);

// get url position for a given rank
int hungarian_url_from_rank(h_problem p, int position, int nElems);

//print assignment
void hungarian_print_assignment(h_problem p);

//print cost matrix
void hungarian_print_costmatrix(h_problem p);

#endif
