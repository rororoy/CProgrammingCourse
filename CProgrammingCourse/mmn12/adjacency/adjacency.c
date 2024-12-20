#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"


/*******************************************************************************

  * Program Name: MMN 12 - Q1 - ADJACENCY MATRIX

  * Description:
    This program recieves from the user a NxN adjacency matrix and checks for
    existance of a path between two nodes.
    The program is internally set up and compiled for a constant N.
    Uses utils.c program file for its helper functions.

  * Algorithm:
    1. Prints an example matrix with null values and asks for input from user.
    2. Loops for each cell in the matrix and asks for an input of 1 or 0 to fill.
    3. If detected EOF - terminates program, handles faulty input to allow only 1 or 0.
    4. If detected faulty input, clears the buffer using clearInputBuffer().
    5. Prints the filled up matrix neetly.
    6. Main part: Asks for two nodes, loops untill EOF or until getting -1 -1.
    7. For each, check if path exists using path(), print if path was found.

  * Input:
    The adjacency matrix values (1 or 0) representing each state of each node in the matrix.

  * Output:
    1. User input/output prompts.
    2. Printing of the matrix.
    3. Whether a path was found between to given nodes u and v.

  * Notes:
    Eample input tests can be found in the same directory as this program. See README.

*******************************************************************************/

int main(){
  adjmat matrix;
  int u, v; /* The two input nodes we use later */
  bool inputcorr; /* Hold the user input */
  int scanres; /* Holds the user input */
  int i,j; /* Iterators */

  printf("The program is setup with a %dx%d adjacency matrix, enter its contents below:\n", N, N);
  printf("Enter 1 or 0 for each coordinate:\n\n");
  printEmptyMatrix();
  printf("\n");

  /* Fill the whole matrix with user input */
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      printf("(%d,%d) = ", i, j);

      /* Get the input from the user and handle faulty input */
      if ((scanres = scanf("%d", (int*)&inputcorr)) == 1){
        if (scanres == EOF){
          printf("ERROR: Reached end of input file\n");
          return 0;} /* If reached EOF exit program*/
        if (inputcorr != 0 && inputcorr != 1){ /* If got a non 0 or 1 digit */
          printf("Error: input can only be 1 or 0, enter the value again\n");
          j--;
        }else{ /* Put in the matrix */
          matrix[i][j] = inputcorr;
        }
      }else{ /* If anything else unexpected */
        printf("Error: input is not a valid number, enter a 1 or 0 value again\n");
        j--;
        clearInputBuffer(); /* Clear input buffer to scan for new input */
      }
    }
  }

  printf("\nThe adjacency matrix was successfuly set up: \n");
  printAdjMatrix(matrix);

  /* Get two coordinates from the user and check for a path */
  printf("\nEnter two values seperated by a sapce to check adjacenty (-1 -1 coordinate to terminate): \n");
  printf("Enter values (between 0 and %d): ", N-1);

  while (scanf(" %d %d", &u, &v) == 2 && !(u == -1 && v == -1)){
    if ((u >= N || v >= N) || (u < 0 || v < 0)) { /* Check if 0 < x,y < N */
      printf("   ERROR: Values must be between 0 and %d", N-1);
    }else{ /* Check otherwise for a path */
      printf("Checking for path from %d to %d  -->  ", u, v);
      printf((path(matrix, u, v)?"Found path":"Didn't find path"));
    }
    printf("\nEnter values (between 0 and %d): ", N-1);
  }

  printf("\nProgram terminated\n");
  return 0;
}
