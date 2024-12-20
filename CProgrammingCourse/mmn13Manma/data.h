#define ASIZE 50
#define BSIZE 100
#define CSIZE 200

int seriesA[ASIZE], seriesB[BSIZE], seriesC[CSIZE], seriesD[10];

typedef struct {
  int comparisons;
  int assigments;
} testvals;

void fillRandom(int arr[], int size);
void printArray(int arr[], int size);
void maxHeapify(int arr[], int i, int size, int d, testvals* results);
void buildMaxHeap(int arr[], int size, int d, testvals* results);
void heapSort(int arr[], int size, int d, testvals* results);
