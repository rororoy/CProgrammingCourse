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
    1. First reads from the user the command and runs through the db of commands
    to see if its a valid command.
    2. If invalid - output error and continue to read another command
       If valid - call the function that has the same name as the command they used
       (through the cmd db that holds pointers to all functions).
    3. Inside one of the functions: define the struct tokanize and pass null defualt values and a function id,
     then call tokanize_input.
    4. tokanize_input will perform multiple tests based on the function id and
    check if the rest of the input is valid (the part after the command itself),
    will return values in fields it extracted from the whole full command of the user via the tokanize var.
    5. tokanize_input will return the specific error it encountered (0 if OK).
    6. given all that tokanize_input has extracted and based on the error the function
    of the command will perform the specific task it was asked and either print a
    result with a print_comp function or end.
    7. Back at the main function - print the error and either terminate incase of a stop or loop and recieve more input.

  * Input:
    Commands in the format <command_name> <vars A-F>,<param 1>,<param 2>
    example: read_comp A, 4.5, -2.3         print_comp A          sub_comp A,B


  * Output:
    Either and error if encountered problem in input
    or printing the result or value of a complex varaible after an operation.

  * Notes:
    Eample input tests can be found in the same directory as this program. See README.
    Some handling of errors may not be as asked in the question because in the forum it was said to do otherwise...

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
