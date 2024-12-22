#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "data.h"

int i, j; /* iterator */
char ch; /* User input whether to print a sorted array or no */


/*******************************************************************************

  * Program Name: MMN 13 - Heapsort efficiency test

  * Description:
    This program performs multiple tests of a Heapsort algorithm on multiple
    d-ary heaps, for d=2,3,4,5.
    The program runs three times on multiple sized arrays at varying lengths.

  * Algorithm:
    The program runs for each of the three series (A through C) and for each,
    will call heapsort on the array, the number of actions performed are counted
    specifically only the number of copies and comparisons via a struct type
    object defined in the header file.
    Heapsort algorithm:
      The way heapsort works is first by converting the array into a max heap.
      Inside max heap, from where the first leaf starts we start moving upwards
      towards the root, each time calling heapify as we move upwards.
      The heapify function checks for a maximum value among all sons of a father
      node and floats the maximum value if found upwards.
      That way all maximum values float upwards and a max heap is constructed in
      the max heap function.
      Back to the main heapsot function, it then places the maximum value at the
      root at the end of the array, then reduce the heap size by one and call
      the heapify function which will float the maximum value upwards to the
      root once again ignoring the value we just placed at the end of the array
      which is the true maximum. That way we get a sorted final array.

  * Input:
    Takes as input three predefined arrays of sizes 50, 100 and 200.
    At the final stage of the program past the main stage: asks the user which
    and whether to print an array post sorting.

  * Output:
    Program modifies the 3 arrays and sorts them, if the user chooses, output
    into the console the sorted arrays.

*******************************************************************************/

int main(){
  testvals testresult = {0, 0}; /* Struct defined in header file to return two values */
  srand(time(NULL)); /* Generate seed */

  fillRandom(seriesA, ASIZE);
  fillRandom(seriesB, BSIZE);
  fillRandom(seriesC, CSIZE);

  printf("Generated 3 randomized series: \n");
  printf("Series A contains %d values   Series B contains %d values", ASIZE, BSIZE);
  printf("   Series C contains %d values\n", CSIZE);

  printf("Starting heapsort comparisons on a d-ary heap for d = 2,3,4,5\n");
  for(i=0; i<3; i++){
    switch(i){
      case 0: printf("\nResults for series A (50 elements)\n"); break;
      case 1: printf("\nResults for series B (100 elements)\n"); break;
      case 2: printf("\nResults for series C (200 elements)\n"); break;
    }
    for(j=2; j<=5; j++){
      /* For d 2 through 5*/
      testresult.comparisons = 0; /* Clear the data from last run */
      testresult.assigments = 0;
      switch(i){
        case 0: heapSort(seriesA, ASIZE, j, &testresult); break;
        case 1: heapSort(seriesB, BSIZE, j, &testresult); break;
        case 2: heapSort(seriesC, CSIZE, j, &testresult); break;
      }
      printf("For d=%d, heapsort made %d comparisons and %d variable assigments\n", j, testresult.comparisons, testresult.assigments);
    }

  }

  /*
    An addition out of question scope: ask if the user wants to print the sorted
     arrays post heapsort.
  */
  printf("\n\nPrint one of the sorted arrays? (enter a,b,c (for series a-c) or n to terminate:");
  while((ch = getchar()) != 'n'){
    printf("\n");
    while (getchar() != '\n'); /* Clear the input buffer */
    switch(ch){
      case 'a': printArray(seriesA, ASIZE); break;
      case 'b': printArray(seriesB, BSIZE); break;
      case 'c': printArray(seriesC, CSIZE); break;
      default: printf("Unkown request");
    }
    printf("\nPrint one of the sorted arrays? (type a,b,c (for series a-c) or n to terminate:");
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

/*
  Given an array and an index, converts an array into a d-ary heap.
*/
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
  if(max != i){
    /* Swap arr[i] and arr[max] */
    arr[i] += arr[max];
    arr[max] = arr[i] - arr[max];
    arr[i] -= arr[max];
    results->assigments+=2; /* Counts the swap */
    maxHeapify(arr, max, size, d, results);
  }
}

/*
  Given an array, create a d-ary heap by going over all the non - leaf
  nodes upwards to the origin/root and heapify down for each node to float the
  max values up.
*/
void buildMaxHeap(int arr[], int size, int d, testvals* results){
  int i;
  for (i = (int)(floor((double)size-2/(double)d)); i>=0; i--){
    maxHeapify(arr, i, size, d, results);
  }
}

/*
  Heapsort algorithm that sorts by making a d-ary heap out of a given array at
  a certain size (d is also passed via attributes).
  Runs from the end of the array towards the start and heapifies each sub tree
  of values at the end of the array.
*/
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
