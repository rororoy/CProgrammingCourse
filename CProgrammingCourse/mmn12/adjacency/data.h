#define N 11
typedef enum {FALSE, TRUE} bool;
typedef bool adjmat[N][N];

bool path(adjmat matrix, int u, int v);
void clearInputBuffer();
void printEmptyMatrix();
void printAdjMatrix(adjmat matrix);
bool path(adjmat matrix, int u, int v);
