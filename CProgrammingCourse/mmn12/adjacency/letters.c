#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "adjacency.h"

int main(){
  adjmat matrix;
  int i, j; /* incrementors */

  printf("The program is setup with a %dx%d matrix, enter its contents below:\n", N, N);
  printf("Enter 1 or 0 for each coordinate:\n\n");

  printf(" ");
  for(i=0, i<N; i++){
    printf(i);
  }

  for (i=0, i<N; i++){
    printf(i)
    for (j=0, j<N, j++){
      printf("*");
    }
  }

}
