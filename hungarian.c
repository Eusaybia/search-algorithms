/*
	=== Weighted Bipartite Graph Minimum Matching Problem ===
	--- solved using a derivation of Hungarian Algorithm  ---

	Algorithm to solve matchign problem briefly described:
		0. Subtract column minima
		1. Initialise matchings by finding minimum val in row and matching the
			row and associated col (if not matched already), else add to
			unchosen/unmatched rows array
		2. While there are unmatched rows:
			Search for an improving path for any unmatched rows
			a. If found, Improve/Update Matchings
			b. Else, Create new zeroes by decreasing unchosen elements to
				produce zeroes, achieved by adjusting decrements and increments
		3. Create final assignment based on matched rows and cols

	The following websites were used to research and develop an implementation
	- https://en.wikipedia.org/wiki/Hungarian_algorithm
	- http://www.hungarianalgorithm.com
	- http://rgrig.appspot.com/static/programs/spoj/scities.pdf
*/

#include "hungarian.h"

#define INF (0x7FFFFFFF) //define infinity (almost)

//Hungarian problem representation
typedef struct hProblemRep{
	int size;
	double** cost;
	int** assignment;
} hProblemRep;

//Static function prototypes called in solveHungarian
static double subtractColMins(hProblem p);
static int match(hProblem p, double * rowDec, int * colMatch, int * rowMatch, int * unchosenRows);

//Prints the current p assignment matrix to stdout
void printHungarianAssignment(hProblem p) {
	printf("\n");
	for (int r = 0; r < p->size; r++) {
		printf(" [");
		for (int c = 0; c < p->size; c++) {
			printf("%5d ",p->assignment[r][c]);
		}
		printf("]\n");
	}
	printf("\n");
}

//Prints the current p cost matrix to stdout
void printHungarianCostMatrix(hProblem p) {
	printf("\n");
	for (int r = 0; r < p->size; r++) {
		printf(" [");
		for (int c = 0; c < p->size; c++) {
			printf("%5.1lf ",p->cost[r][c]);
		}
		printf("]\n");
	}
	printf("\n");
}

//Initialises hungarian problem p
hProblem newHungarian(double** costMatrix, int size) {

	//create and allocate memory to new Hungarian problem p
	hProblemRep *p = (hProblemRep *)malloc(sizeof(hProblemRep));
	assert(p != NULL);

	//set problem size to size of square cost matrix
	p->size = size;

	//allocate memory to 1st dimension of 2d cost and assignment arrays (matrices)
	p->cost = (double**)calloc(size,sizeof(double*));
	assert(p->cost != NULL);
	p->assignment = (int**)calloc(size,sizeof(int*));
	assert(p->assignment != NULL);

	//allocate memory to 2nd dimension of 2d cost and assignment arrays (matrices)
	for (int i = 0; i < p->size; i++) {
		p->cost[i] = (double*)calloc(size,sizeof(double));
		assert(p->cost[i] != NULL);
		p->assignment[i] = (int*)calloc(size,sizeof(int));
		assert(p->assignment[i] != NULL);

		//initialise values of cost matrix to those supplied
		for (int j = 0; j < p->size; j++) {
			p->cost[i][j] =  costMatrix[i][j];
		}
	}

	//return pointer to Hungarian problem p
	return p;
}

//Free all malloced memory associated with the Hungarian problem p
void disposeHungarian(hProblem p) {

	//free 2nd dimension cost and assigment matrix memory
	for (int i = 0; i < p->size; i++) {
		free(p->cost[i]);
		free(p->assignment[i]);
	}
	//free 1st dimension cost and assigment matrix memory
	free(p->cost);
	free(p->assignment);

	//set cost and assignment in problem to NULL
	p->cost = NULL;
	p->assignment = NULL;

	free(p);
}

//Solves Hungarian problem p
double solveHungarian(hProblem p) {
	int nUnchosenRows; //no. of ucnhosen/uncovered rows
	int nRowsExpl; //no. of unchosen rows explored
	int unmatched; //no. of unmatched rows
	int r, c; //row and col counters

	//matchings
	int* colMatch;
	int* rowMatch;
	//e.g. if col c is matched with row r then colMatch[r] == c and rowMatch[c] == r

	int* parentRow; //keep track of preceeding row of col
	int* unchosenRows; //store unchosen/uncovered rows

	double* rowDec; //row decrements
	double* colInc; //col increments
	double* slack; //minimum of each column (ignores chosen rows)
	int* slackRow; //track row where col min occurs for each col

	double cost = 0.0; //cost of assignment

	//allocate memory to our helper arrays
	colMatch = (int*)calloc(p->size,sizeof(int));
	assert(colMatch != NULL);
	unchosenRows = (int*)calloc(p->size,sizeof(int));
	assert(unchosenRows != NULL);
	rowDec  = (double*)calloc(p->size,sizeof(double));
	assert(rowDec != NULL);
	slackRow  = (int*)calloc(p->size,sizeof(int));
	assert(slackRow != NULL);

	rowMatch = (int*)calloc(p->size,sizeof(int));
	assert(rowMatch != NULL);
	parentRow = (int*)calloc(p->size,sizeof(int));
	assert(parentRow != NULL);
	colInc = (double*)calloc(p->size,sizeof(double));
	assert(colInc != NULL);
	slack = (double*)calloc(p->size,sizeof(double));
	assert(slack != NULL);

	//initialise helper arrays to defaults
	for (int i = 0; i < p->size; i++) {
		rowMatch[i] = -1;
		parentRow[i] = -1;
		colInc[i] = 0.0;
		slack[i] = INF;
	}


	//SUBTRACT COLUMN MINIMUMS
	cost += subtractColMins(p);

	//INITIALISE ROW AND COL MATCHINGS/COVERS
	nUnchosenRows = match(p, rowDec, colMatch, rowMatch, unchosenRows);


	//check how many unchosen/uncovered rows
	if (nUnchosenRows == 0) {
		//if none, we are done
		goto done;
	} else {
		//else set unmatched to nUnchosenRows
		unmatched = nUnchosenRows;
	}

	while (1) {

		nRowsExpl = 0; //number of unchosen rows explored

		while (1) {

			//SEARCH FOR AN IMPROVING PATH

			//while more rows to explore
			while (nRowsExpl < nUnchosenRows) {

				//set current row to next unchosen row
				r = unchosenRows[nRowsExpl];

				//loop through cols
				for (c = 0; c < p->size; c++) {
					//only concerned with unchosen cols
					//(note that slack[c] == 0 for chosen cols)
					if (slack[c]) {

						//path weight = cost - row decrements + col increments
						double weight = p->cost[r][c] - rowDec[r] + colInc[c];

						//check if weight is less than current slack
						if (weight < slack[c]) {
							//yes, set new slack
							slack[c] = weight;

							//if slack is 0.0 we have a zero
							if (slack[c] == 0.0) {
								//if no row has been matched so far, we have an improved path
								if (rowMatch[c] < 0) goto breakthrough;
								//set parentRow of c to r
								parentRow[c] = r;
								//add row matched to col to unchosenRows
								unchosenRows[nUnchosenRows++] = rowMatch[c];

							} else {
								//update slack row for col
								slackRow[c] = r;
							}
						}
					}
				}

				//increment no of rows explored
				nRowsExpl++;
			}

			//CREATE NEW ZEROES
			//by decreasing uncovered elements to produce zeroes

			//find smallest element/value of uncovered rows & cols
			double leastVal = INF; //least col min
			//loop through all cols
			for (c = 0; c < p->size; c++) {
				//if the col min in slack[c] is less than leastVal found so far
				if (slack[c] && slack[c] < leastVal)
					//set new leastVal
					leastVal = slack[c];
			}

			//for each row that hasn't been chosen (ie. uncovered)
			for (nRowsExpl=0; nRowsExpl < nUnchosenRows; nRowsExpl++) {
				//increase row decrement by leastVal
				rowDec[unchosenRows[nRowsExpl]] += leastVal;
			}

			//loop through each column
			for (c = 0; c < p->size; c++) {
				//only concerned with unchosen cols
				//(note that slack[c] == 0 for chosen cols)
				if (slack[c]) {

					//update slack values for each column
					slack[c] -= leastVal;

					//if the slack of a col is 0.0, then we have created new zero
					if (slack[c] == 0.0) {
						//get row of newly created zero
						r = slackRow[c];

						//check if col has not been matched (ie. uncovered)
						if (rowMatch[c] < 0) {
							for (int nc = c + 1; nc < p->size; nc++) {
								//if chosen col (ie. slack[c] == 0.0)
								if (slack[nc] == 0.0) {
									//increment col by the leastVal
									colInc[nc] += leastVal;
								}
							}
							//if no row has been matched so far, go to breakthrough
							goto breakthrough;

						} else {
							//set parent row of col to row of newly created 0
							parentRow[c] = r;
							//add the row matching col to unchosenRows
							unchosenRows[nUnchosenRows++] = rowMatch[c];
						}
					}

				} else {
					//increment colInc by leastVal
					colInc[c] += leastVal;
				}
			}

		}


		//IMPROVE MATCHING
		breakthrough:

		while (1) {
			//get old matched col
			int oldCol = colMatch[r];
			//update/set new matching based on current row and col
			colMatch[r] = c;
			rowMatch[c] = r;

			//if oldCol
			if (oldCol < 0)
				break;
			//update current row and col to those corresp. oldCol
			r = parentRow[oldCol];
			c = oldCol;
		}


		//reduce unmatched, check if unmatched is 0
		if (--unmatched == 0)
			//if yes, we are done
			goto done;


		//get ready for another stage
		//re-initialise values to defaults
		nUnchosenRows = 0;
		for (c = 0; c < p->size; c++) {
			parentRow[c]= -1;
			slack[c] = INF;
		}

		for (r = 0; r < p->size; r++)
			if (colMatch[r] < 0) {
				//if no column matched to row, set it as an unchosen row
				unchosenRows[nUnchosenRows++] = r;
			}
	}

	//DONE - CREATE FINAL ASSIGNMENT
	done:
	//loop through each row
	for (int r = 0; r < p->size; r++) {
		//for each row and its matched column set corresponding assignment to 1
		p->assignment[r][colMatch[r]] = 1;
	}

	//loop through each row
	for (int r = 0; r < p->size; r++) {
		//increase cost by row decrements
		cost += rowDec[r];
	}

	//loop though each col
	for (int c = 0; c < p->size; c++) {
		//reduce cost by col increments
		cost -= colInc[c];
	}

    //free helper arrays
	free(slack);
	free(colInc);
	free(parentRow);
	free(rowMatch);
	free(slackRow);
	free(rowDec);
	free(unchosenRows);
	free(colMatch);

    //return cost of assignment
    return cost;

}

//STATIC: Subtracts column mins in p
static double subtractColMins(hProblem p) {

	//row and col counters
	int r, c;
	//total cost
	double tCost = 0.0;
	//loop through each column
	for (c = 0; c < p->size; c++) {
		//set inital colMin to first [0] element of col
		double colMin = p->cost[0][c];
		//loop through all rows in col (ie. all elements of col)
		for (r = 1; r < p->size; r++) {
			//check if cost < s
			if (p->cost[r][c] < colMin) {
				//yes, set new colMin to cost
				colMin = p->cost[r][c];
			}
		}
		//add colMin to cost
		tCost += colMin;
		//if colMin isnt 0
		if (colMin != 0.0)
			//remove colMin from each col entry, row by row
			for (r = 0; r < p->size; r++)
				p->cost[r][c] -= colMin;
	}
	return tCost;

}

//STATIC: Matches rows & cols in p
static int match(hProblem p, double * rowDec, int * colMatch, int * rowMatch, int * unchosenRows) {

	int nUnchosenRows = 0;
	int r, c; //row and col counters

    //loop through each row
	for (r = 0; r < p->size; r++) {
        //get the rowMin
        //set inital rowMin to first element of row
		double rowMin = p->cost[r][0];
        //loop through each column
		for (c = 1; c < p->size; c++) {
            //check if cost at current [r][c] < the current rowMin
            if (p->cost[r][c] < rowMin)
                //if yes, set new rowMin
				rowMin = p->cost[r][c];
        }

        //set row decrement to found rowMin
        rowDec[r] = rowMin;

        //declare and initialise rowDone flag
        int rowDone = 0;

        //loop through each col in current row (r)
		for (c = 0; c < p->size; c++) {
            //if we find element equal to rowMin that hasn't been matched to another row
			if (rowMin == p->cost[r][c] && rowMatch[c] < 0) {
                //set match
				colMatch[r] = c;
				rowMatch[c] = r;

                //set rowDone flag
				rowDone = 1; break;
            }
        }

		//if we aren't done with row, ie. the rowMin column has been matched to another row
        if (!rowDone) {
			//set col match for row to -1
            colMatch[r]= -1;
			//set next unchosen row to current row
            unchosenRows[nUnchosenRows++] = r;
        }
	}
	//return no of unchosen/uncovered rows
	return nUnchosenRows;
}
