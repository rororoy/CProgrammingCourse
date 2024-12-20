#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

/*******************************************************************************

  * Program Name: MMN 12 - ADJACENCY MATRIX UTILITIES

  * Description:
    This program contains helper functions for the main adjacency matrix program.

*******************************************************************************/

/*
  Clears the input buffer by looping over all faulty input untill EOF
*/
void clearInputBuffer(){
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

/*
  Prints an example of a NxN matrix for the user.
*/
void printEmptyMatrix(){
  int i,j; /* Iterators */
  printf("| X |");
  for (i=0; i<N; i++){
    if (i>9){ printf("| %d|", i); }
    else if (i>99){ printf("|%d|", i); }
    else{printf("| %d |", i);}
  }
  printf("\n");
  for (i=0; i<N; i++){
    if (i>9){ printf("| %d|", i); }
    else if (i>99){ printf("|%d|", i); }
    else{printf("| %d |", i);}
    for (j=0; j<N; j++){
      printf("| * |");
    }
    printf("\n");
  }
}

/*
  Given an adjacency matrix, prints its contents neetly.
*/
void printAdjMatrix(adjmat matrix){
  int i,j; /* Iterators */
  printf("| X |");
  for (i=0; i<N; i++){
    if (i>9){ printf("| %d|", i); }
    else if (i>99){ printf("|%d|", i); }
    else{printf("| %d |", i);}
  }
  printf("\n");
  for (i=0; i<N; i++){
    if (i>9){ printf("| %d|", i); }
    else if (i>99){ printf("|%d|", i); }
    else{printf("| %d |", i);}
    for (j=0; j<N; j++){
      printf("| %d |", (int)matrix[i][j]);
    }
    printf("\n");
  }
}

/*
  Given an adjacency matrix returns a bool object TRUE/FALSE if a path exists
  between the two given nodes u and v.
  Does so recursivly, for each intial node u, checks for all the neigbhours of u
  (by checking if encountered a value of 1 in the row of u), for each neigbhour,
  checks if a path exists between the neigbhour and the target v. Sums all the
  results returned from the calls to path into one varaible result, if a path was
  found somewhere, return TRUE, else reuslt remains FALSE.
  Recursion end case is reaching a leaf node (source=target <==> u=v)
*/
bool path(adjmat matrix, int u, int v){
  int i;
  bool result = FALSE;

  if(u==v){return TRUE;}

  for (i=0; i<N; i++){
    /* printf("Looking at %d, with: %d\n", u, i); */
    if(matrix[u][i] == 1){
      /* printf("Entered into %d\n", i); */
      result = path(matrix, i, v) || result;
    }
  }
  /* printf("Didnt find at %d\n", u); */
  return result;
}
