#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "data.h"

int i, j; /* iterator */

int main(){
  testvals testresult = {0, 0}; /* Struct defined in header file to return two values */
  srand(time(NULL)); /* Generate seed */

  fillRandom(seriesA, ASIZE);
  fillRandom(seriesB, BSIZE);
  fillRandom(seriesC, CSIZE);
  fillRandom(seriesD, 10);

  printf("Generated 3 randomized series: \n");
  printf("Series A contains %d values   Series B contains %d values", ASIZE, BSIZE);
  printf("   Series C contains %d values\n", CSIZE);

  /*
  printArray(seriesD, 10);
  printArray(seriesA, ASIZE);
  printArray(seriesB, BSIZE);
  printArray(seriesC, CSIZE);
  */

  printf("Starting heapsort comparisons on a d-ary heap for d = 2,3,4,5\n");
  for(i=0; i<3; i++){
    switch(i){
      case 0: printf("\nResults for series A (50 elements)\n"); break;
      case 1: printf("\nResults for series B (100 elements)\n"); break;
      case 2: printf("\nResults for series C (200 elements)\n"); break;
    }
    for(j=2; j<=5; j++){
      /* For d 2 trhough 5*/
      testresult.comparisons = 0;
      testresult.assigments = 0;
      switch(i){
        case 0: heapSort(seriesA, ASIZE, j, &testresult); break;
        case 1: heapSort(seriesB, BSIZE, j, &testresult); break;
        case 2: heapSort(seriesC, CSIZE, j, &testresult); break;
      }
      printf("For d=%d, heapsort made %d comparisons and %d variable assigments\n", j, testresult.comparisons, testresult.assigments);
    }
  }
  return 0;
}

/*
  Given the size if the array, fills it up with random values (range 0-2023)
*/
void fillRandom(int arr[], int size){
  for(i=0; i<size; i++){
    arr[i] = rand() % 1024;
  }
}

/*
  Given an array print its contents
*/
void printArray(int arr[], int size) {
    for (i = 0; i < size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf("\n");
}

void maxHeapify(int arr[], int i, int size, int d, testvals* results){
  int max = i;
  int k;
  for(k=0; k<d; k++){ /* Iterate over all the d children */
    results->comparisons++; /* Counts if comparison */
    if((d*i+k+1) < size && arr[d*i+k+1] > arr[i]){
      results->comparisons++; /* Counts if comparison */
      if(arr[d*i+k+1] > arr[max]){
        max = d*i+k+1;
      }
    }
  }
  results->comparisons++; /* Counts if comparison */
  if(max != i){
    /* Swap arr[i] and arr[max] */
    arr[i] += arr[max];
    arr[max] = arr[i] - arr[max];
    arr[i] -= arr[max];
    results->assigments+=2; /* Counts the swap */
    maxHeapify(arr, max, size, d, results);
  }

}


void buildMaxHeap(int arr[], int size, int d, testvals* results){
  int i;
  for (i = (int)(floor((double)size-2/(double)d)); i>=0; i--){
    maxHeapify(arr, i, size, d, results);
  }
}


void heapSort(int arr[], int size, int d, testvals* results){
  int i;
  buildMaxHeap(arr, size, d, results);
  for(i=size-1; i>0; i--){
    /* Swap arr[i] and arr[1] */
    arr[i] += arr[0];
    arr[0] = arr[i] - arr[0];
    arr[i] -= arr[0];
    results->assigments+=2; /* Counts the swap */
    size--;
    maxHeapify(arr, 0, size, d, results);
  }
}
