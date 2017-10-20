#define N_ROWS 100
#define MAX_LISTS 100
#define MAX_CHAR 256

void readRankFile(char *filename, int *array, int *maxRows);
int argsOk(int argc, char *argv[]);
void insertSetArray(int *array, int *nElems, int size, int elem);
int cmpInt(const void *a, const void *b);
int findRankListSize(int rankArray[], int maxUrls);
int findUrlPositionInRankList(int rankArray[], int url, int maxUrls);
double scaledFootruleDistance(int rankArrays[MAX_LISTS][N_ROWS], int n, int p, int tc, int ti);