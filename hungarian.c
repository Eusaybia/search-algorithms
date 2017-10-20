#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hungarian.h"

#define INF (0x7FFFFFFF)//define infinity (almost)

typedef struct h_problem_rep {
	int size ;
	double **cost ;
	int **assignment ;
} h_problem_rep ;

//returns total cost
static double subtractColMins(h_problem p) {

	//row and col counters
	int r, c ;
	//total cost
	double tCost = 0.0 ;
	//loop through each column
	for (c = 0 ; c < p->size ; c++){
		//set inital colMin to first [0] element of col
		double colMin = p->cost[0][c] ;
		//loop through all rows in col (ie. all elements of col)
		for (r = 1 ; r < p->size ; r++)
			//check if cost < s
			if (p->cost[r][c] < colMin)
				//yes, set new colMin to cost
				colMin = p->cost[r][c] ;
		//add colMin to cost
		tCost += colMin ;
		//if colMin isnt 0
		if (colMin != 0)
			//remove colMin from each col entry, row by row
			for (r = 0 ; r < p->size ; r++)
				p->cost[r][c] -= colMin ;
	}

	return tCost ;

}

//returns number of unchosen rows
static int match(h_problem p, double *row_dec, int *col_match, int *row_match, int *unchosen_row) {

	int nUnchosenRows = 0 ;
	int r, c ;	//row and col counters

	//loop through each row
	for (r = 0 ; r < p->size ; r++){
		//get the rowMin
		//set inital rowMin to first element of row
		double rowMin = p->cost[r][0] ;
		//loop through each column
		for (c = 1 ; c < p->size ; c++){
			//check if cost at current [r][c] < the current rowMin
			if (p->cost[r][c] < rowMin)
				//if yes, set new rowMin
				rowMin = p->cost[r][c] ;
		}

		//set row dercrement to found rowMin
		row_dec[r] = rowMin ;

		//declare and initialise rowDone flag
		int rowDone = 0 ;

		//loop through each col in current row (r)
		for (c = 0 ; c < p->size ; c++){
			//if we find element equal to rowMin that hasn't been matched
			if (rowMin == p->cost[r][c] && row_match[c] < 0){
				//set match
				col_match[r] = c ;
				row_match[c] = r ;

				//set rowDone flag
				rowDone = 1 ; break ;
			}
		}

		//if we aren't done with row
		if (!rowDone){
			//set col match for row to -1
			col_match[r] = -1 ;
			//set next unchosen row to current row
			unchosen_row[nUnchosenRows++] = r ;
		}
	}
	//return no of unchosen rows
	return nUnchosenRows ;

}

int hungarian_url_from_rank(h_problem p, int position, int nElems) {
	for (int y = 0 ; y < nElems ; y++){
		if (p->assignment[y][position]) return y ;
	}
	fprintf(stderr, "No url found for this position, incorrect assignment!\n") ;
	return -1 ;
}

void hungarian_print_assignment(h_problem p) {
	int i, j ;
	fprintf(stderr, "\n") ;
	for (i = 0 ; i < p->size ; i++){
		fprintf(stderr, " [") ;
		for (j = 0 ; j < p->size ; j++){
			fprintf(stderr, "%5d ", p->assignment[i][j]) ;
		}
		fprintf(stderr, "]\n") ;
	}
	fprintf(stderr, "\n") ;
}

void hungarian_print_costmatrix(h_problem p) {
	int i, j ;
	fprintf(stderr, "\n") ;
	for (i = 0 ; i < p->size ; i++){
		fprintf(stderr, " [") ;
		for (j = 0 ; j < p->size ; j++){
			fprintf(stderr, "%5.2lf ", p->cost[i][j]) ;
		}
		fprintf(stderr, "]\n") ;
	}
	fprintf(stderr, "\n") ;
}

void hungarian_print_status(h_problem p) {

	fprintf(stderr, "cost:\n") ;
	hungarian_print_costmatrix(p) ;

	fprintf(stderr, "assignment:\n") ;
	hungarian_print_assignment(p) ;

}

h_problem hungarian_init(double **cost_matrix, int size) {

	h_problem_rep *p = (h_problem_rep *)malloc(sizeof(h_problem_rep)) ;
	assert(p != NULL) ;

	//set problem size to size of square cost matrix
	p->size = size ;

	//allocate memory to 1st dimension of 2d cost and assignment arrays (matrices)
	p->cost = (double **)calloc(size, sizeof(double *)) ;
	assert(p->cost != NULL) ;
	p->assignment = (int **)calloc(size, sizeof(int *)) ;
	assert(p->assignment != NULL) ;

	//allocate memory to 2nd dimension of 2d cost and assignment arrays (matrices)
	for (int i = 0 ; i < p->size ; i++){
		p->cost[i] = (double *)calloc(size, sizeof(double)) ;
		assert(p->cost[i] != NULL) ;
		p->assignment[i] = (int *)calloc(size, sizeof(int)) ;
		assert(p->assignment[i] != NULL) ;

		//initialise values of cost matrix to those supplied
		for (int j = 0 ; j < p->size ; j++){
			p->cost[i][j] =  cost_matrix[i][j] ;
		}
	}

	return p ;
}

void hungarian_free(h_problem p) {

	//free 2nd dimension cost and assigment matrix memory
	for (int i = 0 ; i < p->size ; i++){
		free(p->cost[i]) ;
		free(p->assignment[i]) ;
	}
	//free 1st dimension cost and assigment matrix memory
	free(p->cost) ;
	free(p->assignment) ;

	//set cost and assignment in problem to NULL
	p->cost = NULL ;
	p->assignment = NULL ;
}

double hungarian_solve(h_problem p) {
	int j, unmatched, nUnchosenRows, nRowsExpl ;
	int r, c ;	//row and col counters
	double s ;

	//matchings
	int *col_match ;
	int *row_match ;
	//e.g. if col c is matched with row r then col_match[r] == c and row_match[c] == r

	int *parent_row ;	//keep track of preceeding row
	int *unchosen_row ;	//

	double *row_dec ;	//row decrements
	double *col_inc ;	//col increments
	double *slack ;	//minimum of each column (ignores chosen rows)
	int *slack_row ;//track row where col min occurs for each col

	double cost = 0.0 ;	//cost of assignment

	//allocate memory to our helper arrays
	col_match = (int *)calloc(p->size, sizeof(int)) ;
	assert(col_match != NULL) ;
	unchosen_row = (int *)calloc(p->size, sizeof(int)) ;
	assert(unchosen_row != NULL) ;
	row_dec  = (double *)calloc(p->size, sizeof(double)) ;
	assert(row_dec != NULL) ;
	slack_row  = (int *)calloc(p->size, sizeof(int)) ;
	assert(slack_row != NULL) ;

	row_match = (int *)calloc(p->size, sizeof(int)) ;
	assert(row_match != NULL) ;
	parent_row = (int *)calloc(p->size, sizeof(int)) ;
	assert(parent_row != NULL) ;
	col_inc = (double *)calloc(p->size, sizeof(double)) ;
	assert(col_inc != NULL) ;
	slack = (double *)calloc(p->size, sizeof(double)) ;
	assert(slack != NULL) ;

	//initialise helper arrays to defaults
	for (int i = 0 ; i < p->size ; i++){
		row_match[i] = -1 ;
		parent_row[i] = -1 ;
		col_inc[i] = 0.0 ;
		slack[i] = INF ;
	}


	// SUBTRACT COLUMN MINIMUMS
	cost += subtractColMins(p) ;
	// END ------------------------

	// MATCHING ROWS AND COLS
	nUnchosenRows = match(p, row_dec, col_match, row_match, unchosen_row) ;
	//END


	//check how many unchosen rows
	if (nUnchosenRows == 0){
		//if none, we are done
		goto done ;
	}
	else {
		//else set unmatched to nUnchosenRows
		unmatched = nUnchosenRows ;
	}

	while (1){

		nRowsExpl = 0 ;	//number of unchosen rows explored

		while (1){

			//while more rows to explore
			while (nRowsExpl < nUnchosenRows){

				// Begin explore next node/row (nRowsExpl)

				//set current row to next unchosen row
				r = unchosen_row[nRowsExpl] ;
				//set the rowMin to row_dec[r] calculated in matchRowCol
				double rowMin = row_dec[r] ;

				//loop through each col in row
				for (c = 0 ; c < p->size ; c++){
					//if col has a min
					if (slack[c]){


						double del = p->cost[r][c] - rowMin + col_inc[c] ;

						if (del < slack[c]){
							if (del == 0.0){
								if (row_match[c] < 0) goto breakthrough ;

								slack[c] = 0.0 ;
								parent_row[c] = r ;

								unchosen_row[nUnchosenRows++] = row_match[c] ;
							}
							else {
								slack[c] = del ;
								slack_row[c] = r ;
							}
						}
					}
				}

				//increment no of rows explored
				nRowsExpl++ ;
			}

			// INTRODUCE NEW ZEROES, by decresing uncovered elements to produce zeroes

			s = INF ;
			for (c = 0 ; c < p->size ; c++){
				if (slack[c] && slack[c] < s)
					s = slack[c] ;
			}
			for (nRowsExpl = 0 ; nRowsExpl < nUnchosenRows ; nRowsExpl++){
				row_dec[unchosen_row[nRowsExpl]] += s ;
			}

			for (c = 0 ; c < p->size ; c++)
				if (slack[c]){
					slack[c] -= s ;
					if (slack[c] == 0){

						// look at newly created zeroes
						r = slack_row[c] ;

						//Decreasing uncovered elements produces zero at [r,c]
						if (row_match[c] < 0){
							for (j = c + 1 ; j < p->size ; j++)
								if (slack[j] == 0.0)
									col_inc[j] += s ;
							goto breakthrough ;

						}
						else {
							parent_row[c] = r ;
							unchosen_row[nUnchosenRows++] = row_match[c] ;
						}
					}

				}
				else {
					col_inc[c] += s ;
				}

		}


breakthrough:
		// UPDATE MATCHING

		while (1){
			j = col_match[r] ;
			col_match[r] = c ;
			row_match[c] = r ;

			if (j < 0)
				break ;
			r = parent_row[j] ;
			c = j ;
		}
		//END --------------

		//reduce unmatched, check if unmatched is 0
		if (--unmatched == 0)
			//if yes, we are done
			goto done ;


		// Get ready for another stage
		//re-initialise values to defaults
		nUnchosenRows = 0 ;
		//loop through each col
		for (c = 0 ; c < p->size ; c++){
			parent_row[c] = -1 ;
			slack[c] = INF ;
		}
		//loop through each row
		for (r = 0 ; r < p->size ; r++)
			if (col_match[r] < 0){
				unchosen_row[nUnchosenRows++] = r ;
			}
	}



	//DONE//

done:
	//loop through each row
	for (int r = 0 ; r < p->size ; r++){
		//for each row and its col match entry set corresponding assignment to 1
		p->assignment[r][col_match[r]] = 1 ;
	}

	//loop through each row
	for (int r = 0 ; r < p->size ; r++){
		//increase cost by row decrements
		cost += row_dec[r] ;
	}

	//loop though each col
	for (int c = 0 ; c < p->size ; c++){
		//reduce cost by col increments
		cost -= col_inc[c] ;
	}

	//free helper arrays
	free(slack) ;
	free(col_inc) ;
	free(parent_row) ;
	free(row_match) ;
	free(slack_row) ;
	free(row_dec) ;
	free(unchosen_row) ;
	free(col_match) ;

	//return cost of assignment
	return cost ;

}
