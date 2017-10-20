#define N_ROWS 100
#define MAX_LISTS 100
#define MAX_CHAR 256

typedef struct UrlRep *Url;

Url newUrl();
void readRankFile(char *filename, Url *array, int *maxRows);
int argsOk(int argc, char *argv[]);
void insertSetArray(Url *array, int *nElems, int size, Url elem);
int cmpString(const void *a, const void *b);
int findRankListSize(Url rankArray[], int maxUrls);
int findUrlPositionInRankList(Url rankArray[], Url url, int maxUrls);
double scaledFootruleDistance(int n, int p, int tc, int ti);