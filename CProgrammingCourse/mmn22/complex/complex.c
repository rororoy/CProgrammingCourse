#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

/*******************************************************************************

  * Program Name: MMN 22  - COMPLEX NUMBER FUNCTIONS

  * Description:
    This file defines the functions used in the main mycomp program
    Utilizes the same alogorithm of tokanize_input as described in the mycomp program.

*******************************************************************************/

/* Define the cmpnums array - holds all the pointers to the complex number variables */
cmpnums_struct cmpnums[] = {
    {'A', &A},
    {'B', &B},
    {'C', &C},
    {'D', &D},
    {'E', &E},
    {'F', &F},
    {'#', NULL} /* Marks the end */
};

/* Define the db for all possible error types with its own error code (0-10) */
errors_struct errors[] = {
  {0, "OK"},
  {1, "Undefined complex variable"},
  {2, "Undefined command name"},
  {3, "Invalid parameter - not a number"},
  {4, "Missing parameter"},
  {5, "Extraneous text after end of command"},
  {6, "Multiple consecutive commas"},
  {7, "Missing comma"},
  {8, "Illegal comma"},
  {9, "Program terminated"},
  {10, "Program terminated incorrectly - use stop"}
};

/*
  Called by the read_comp command by the user
  Passes parameters into the tokanize_input function
  After tokanizing input, recieves returned parameters that were extracted from the user
  In our case: A target complex number to change its value and two double numbers
  that are the real and img parts of the complex number

  If no error was ecnountered while tokanizing - update the value of the complex number.
*/
void read_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 0, 0, 0, NULL}; /* read_comp id is 0 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real = extracted_tokens.return_param1;
    extracted_tokens.target->img = extracted_tokens.return_param2;
  }
}

/*
  Called by the print_comp command by the user
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the target comlex number
  If no errors were encountered - print the target complex number (A-F)
*/
void print_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 1, 0, 0, NULL}; /* print_comp id is 1 */
  if(!(error = tokenize_input(&extracted_tokens))){
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Internal complex print function
  Called only internally from the print_comp functoin
  Recieves a complex number pointer and prints its contents in the right format:
  (x) + (y)i  or  (x) - (y)i
*/
void print_comp_internal(complex *comp){
  if(comp->img < 0){
    printf("%.2f - (%.2f)i\n",comp->real, fabs(comp->img));
  }else{
    printf("%.2f + (%.2f)i\n",comp->real, comp->img);
  }
}

/*
  Called by the add_comp command by the user
  Add two complex numbers to each other and saves the result in to the first one
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the two complex number pointers
  If no errors were encountered - add the target complex number with the additional
   complex number and update the value of the target complex number
*/
void add_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 2, 0, 0, NULL}; /* add_comp id is 2 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real += extracted_tokens.return_param3->real;
    extracted_tokens.target->img += extracted_tokens.return_param3->img;
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Called by the sub_comp command by the user
  Subtracts two complex numbers from each other and saves the result in to the first one
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the two complex number pointers
  If no errors were encountered - subtract the target complex number with the additional
  complex number and update the value of the target complex number (sub A,B --> A = A-B)
*/
void sub_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 3, 0, 0, NULL}; /* add_comp id is 3 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real -= extracted_tokens.return_param3->real;
    extracted_tokens.target->img -= extracted_tokens.return_param3->img;
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Called by the mult_comp_real command by the user
  Calculates multiplication of a comlex number by a given real number and saves
  the result into the complex number
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the target complex numberp pointer and the real number
  If no errors were encountered - calculate based on the multiplication equation
*/
void mult_comp_real(void){
  int error;
  tokenized extracted_tokens = {NULL, 4, 0, 0, NULL}; /* mult_comp_real id is 4 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real *= extracted_tokens.return_param1;
    extracted_tokens.target->img *= extracted_tokens.return_param1;
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Called by the mult_comp_img command by the user
  Calculates multiplication of a comlex number by a given imaginary number and saves
  the result into the complex number
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the target complex numberp pointer and the imaginary number
  If no errors were encountered - calculate based on the multiplication equation
*/
void mult_comp_img(void){
  int error;
  tokenized extracted_tokens = {NULL, 5, 0, 0, NULL}; /* mult_comp_real id is 4 */
  if(!(error = tokenize_input(&extracted_tokens))){
    int temp_real = extracted_tokens.target->real;
    extracted_tokens.target->real = -(extracted_tokens.return_param1 * extracted_tokens.target->img);
    extracted_tokens.target->img = extracted_tokens.return_param1 * temp_real;
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Called by the mult_comp_img command by the user
  Calculates multiplication of a comlex number by another compelx number
  save the result into the target complex number
  Passes null parameters into the tokanize_input function and the function id
  After tokanizing input, recieves the two complex numbers pointers
  If no errors were encountered - calculate based on the multiplication equation
*/
void mult_comp_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 6, 0, 0, NULL}; /* mult_comp_comp id is 6 */
  if(!(error = tokenize_input(&extracted_tokens))){
    /* (a+bi)*(c+di) = (ac-bd)+(ad+bc)i */
    int temp_real = extracted_tokens.target->real;
    extracted_tokens.target->real = (extracted_tokens.target->real * extracted_tokens.return_param3->real) - (extracted_tokens.target->img * extracted_tokens.return_param3->img);
    extracted_tokens.target->img = (temp_real * extracted_tokens.return_param3->img) + (extracted_tokens.target->img * extracted_tokens.return_param3->real);
    print_comp_internal(extracted_tokens.target);
  }
}

/*
  Called by the abs_comp command by the user
  Calculates the abosulte value of a given complex number
  Recieves after tokanization - the target complex number pointer
  If no error encountered - prints the abs value of the compelx number
*/
void abs_comp(void){
  int error;
  tokenized extracted_tokens = {NULL, 7, 0, 0, NULL}; /* abc_comp id is 7 */
  if(!(error = tokenize_input(&extracted_tokens))){
    double calculated_abs = sqrt((extracted_tokens.target->real*extracted_tokens.target->real) + (extracted_tokens.target->img*extracted_tokens.target->img));
    printf("%.2f\n", (calculated_abs));
  }
}

/*
  Called by the stop command by the user
  The function will scan the buffer input and see if nothing follows after the
  stop command and pass back to the main function error 9 signaling the program
  should finish taking input and terminate correctly, if error ecnountered -
  do not terminate and return the error encountered
*/
int stop(void){
  int skip;
  char actual_buffer[100];
  char *buffer = actual_buffer;
  char ch;

  /* Get the rest of the command from stdin and store in a buffer */
  if(fgets(actual_buffer, sizeof(actual_buffer), stdin) != NULL){
    int len = strlen(actual_buffer);
    if(len>0 && actual_buffer[len-1] == '\n'){
      /* Strip nl char at the end of the input */
      actual_buffer[len-1] = '\0';
    }

    /* Extract first non whitespace char */
    skip = strspn(actual_buffer, " \t\r\n"); /* Skip whitespace and get first param */
    buffer += skip;
    ch = buffer[0];

    /* check if command has extraneous text at the end */
    if(ch != '\0'){return 5;} /* Extraneous text at the end */
    else{return 9;} /* Program terminated */
  }
  return 10; /* Terminated incorrectly */
}
