#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASIZE 50
#define BSIZE 100
#define CSIZE 200

int seriesA[ASIZE], seriesB[BSIZE], seriesC[CSIZE];
int i; /* iterator */

void fillRandom(int arr[], int size);
void printArray(int arr[], int size);
void heapSort(int arr[], int size, int d);

int main(){
  srand(time(NULL));

  fillRandom(seriesA, ASIZE);
  fillRandom(seriesB, BSIZE);
  fillRandom(seriesC, CSIZE);

  printArray(seriesA, ASIZE);
  printArray(seriesB, BSIZE);
  printArray(seriesC, CSIZE);

  /*
  */

  return 0;
}

void fillRandom(int arr[], int size){
  for(i=0; i<size; i++){
    arr[i] = rand() % 1024;
  }
}

void printArray(int arr[], int size) {
    for (i = 0; i < size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf("\n");
}

void heapSort(int arr[], int size, int d){

}
