#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"

/*
TODO handle EOF in the middle of input - should stop and error
*/

/*******************************************************************************

  * Program Name: MMN 22  - COMPLEX NUMBER CALCULATOR

  * Description:
    This program is a complex number calculator that allows a user to define
    complex numbers labled A-F and perform mathematical operations on them and see the results.

  * Variables and data structures:
    1. complex - a struct type structure that holds two parameters: the real and imaginary parts of a complex number.
    2. complex numbers A-F are defined (initialized by auto as 0+0i) in the main file and are the only complex
    numbers the user can use.
    3. cmp and cmd structs serve as database that hold a name(string) parameter and pointers to the vars/functions.
    4. error struct - holds a field of an error index and the type of error -
    used to print to the user specific errors from predefined errors.
    5. tokanized - this struct holds multiple parameters and is used to pass parameters between functions
    when calling a void function (like all that handle each command) parameters can only be passed via the
    tokanized struct to allow all functions to remain without parameters.
    The function tokanize_input will read input and sort it in the correct parameters of the tokanized object:
      a. target - a pointer to a complex number variable - the read number(A-F) to do operations on
      b. fnc_id - a predefined field that is passed from the command functions that called tokanize_input (each command has an id)
      c. return return_param1, return_param2 - two double numbers that are returned back from tokanize_input (used for read_comp)
      d. return_param3 - a pointer to a complex number varaible - extracted incase the second field of the command is another
      complex num (like in sub_comp, add_comp).
    5. error - a global variable that holds at anytime the id of the specific error currently encountered across the program

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
      Some handling of errors may not be as asked in the question because in the forum it was said to do otherwise....

*******************************************************************************/

/* Define the complex variables */
complex A = {0.0, 0.0};
complex B = {0.0, 0.0};
complex C = {0.0, 0.0};
complex D = {0.0, 0.0};
complex E = {0.0, 0.0};
complex F = {0.0, 0.0};

int main(){
  char command[30];
  int i;
  char ch; /* Temp char */
  int result;

  printf("Initialized complex numbers A-F to default values of 0+0i\n");
  printf("Please enter a valid command out of possible commands:\n");
  for(i=0; cmd[i].func != NULL; i++){
    printf("%s ", cmd[i].name);
  }
  printf("\n\n");

  for(;;){
    printf("> ");
    if((result = scanf("%s", command)) == 1){
      for(i=0; cmd[i].func != NULL; i++){
        if(strcmp(command, cmd[i].name)==0){
          /* If found match for the command */
          break;
        }
      }

      if(cmd[i].func == NULL){
        if((unsigned char)command[strlen(command)-1] == ','){error = 8;} /* Illegal comma */
        else{error = 2;} /* Undefined command */

        while((ch=getchar()) != '\n' && ch != EOF){/*Clear buffer chars*/}
      }else{
        (*(cmd[i].func))(); /* Call and execute correct function */
      }

      if(error != 0){
        /* printf("\nERROR %d", error); */
        printf("\n%s\n", errors[error].error_msg);
      }

      if(error == 9 || error == 10){
        break;
      }
    }else if(result == EOF){
      error = 10; /* Program terminated incorrectly error */
      printf("\n%s\n", errors[error].error_msg);
      break;
    }
  }

  return 0;
}
