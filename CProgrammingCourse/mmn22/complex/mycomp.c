#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"

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

/* The error variable holds the error code the program encountered while running */
static int error;


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

  /* Define the cmd array - holds all the pointers to possible command functions */
  cmd_struct cmd[] = {
    {"read_comp", read_comp},
    {"print_comp", print_comp},
    {"add_comp", add_comp},
    {"sub_comp", sub_comp},
    {"mult_comp_real", mult_comp_real},
    {"mult_comp_img", mult_comp_img},
    {"mult_comp_comp", mult_comp_comp},
    {"abs_comp", abs_comp},
    {"stop", abs_comp},
    {"not_valid", NULL}
  };

  printf("Initialized complex numbers A-F to default values of 0+0i\n");
  printf("Please enter a valid command out of possible commands:\n");
  for(i=0; cmd[i].func != NULL; i++){
    printf("%s ", cmd[i].name); /* Print list of commands */
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
        if(strcmp(command, "stop") == 0){
          error = stop(); /* Manually call the stop function from complex.c */
        }
        else{
          (*(cmd[i].func))(); /* Call and execute correct function */
        }
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

/*
  Given the tokanized object with null values and a certain function_id:
  Gets the input from the user, handles it and sets all the params it
  extracted and returns the error code it encountered, all based on the function id it recieves.

  Defines a char buffer that will store the whole line of input from stdin into it
  iterate over the buffer to check the different expected fields if valid
  For each parameter it successfully extracted it will "put" into the tokanized object
*/
int tokenize_input(tokenized *extracted_tokens){
  char var_name;
  double r, i;
  int skip; /* Hold amount of chars of whitespace to skip */
  char ch;
  char partial[INPUT_BUFFER_SIZE]; /* A partial buffer used to store substrings of the buffer */
  int j = 0; /* Iterator */
  int dot_count=0;
  char actual_buffer[INPUT_BUFFER_SIZE];
  char *buffer = actual_buffer; /* Pointer to the actual buffer so that we can traverse it easily */
  char *endptr; /* Points to the end of the partial buffer after conversion of the substring to a number */
  int func_id = extracted_tokens->func_id;

  /* Get the rest of the command from stdin and store in a buffer */
  if(fgets(actual_buffer, sizeof(actual_buffer), stdin) != NULL){
    int len = strlen(actual_buffer);
    if(feof(stdin)){error =  10; return 10;}
    if(len>0 && actual_buffer[len-1] == '\n'){
      /* Strip nl char at the end of the input */
      actual_buffer[len-1] = '\0';
    }

    /* Extract var_name */
    skip = strspn(actual_buffer, " \t\r\n"); /* Skip whitespace and get first param */
    buffer += skip;
    var_name = buffer[0];

    if(var_name == EOF){error = 10; return 10;} /* Detected EOF in the middle - output error #10*/

    for(j=0; cmpnums[j].name != '#'; j++){
      if(cmpnums[j].name == var_name){
        /* If found match for the command */
        break;
      }
    }

    if(cmpnums[j].name == '#'){
      if(var_name == ','){error = 8; return 8;} /* Illegal comma */

      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
      buffer += skip;

      if(buffer[0] == '\0'){error = 4; return 4;}

      error = 1; return 1; /* Undefined complex var */
    }else{
      extracted_tokens->target = cmpnums[j].cmplx;
    }

    /*******************************************************/
    /* If the command is print_comp (id=1) or abs_comp (id=7) */
    if(func_id == 1 || func_id == 7){
      if(buffer[1] == '\0'){error =  0; return 0;} /* If was terminated well */

      buffer += 1;

      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
      buffer += skip;

      if(buffer[0] == EOF){error =  10; return 10;} /* Detected EOF in the middle - output error #10*/

      if(buffer[0] != '\0'){error =  5; return 5;} /* Extraneous text at end */
      return 0;
    }

    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected comma */
    buffer += skip;
    ch = buffer[0];

    if(buffer[0] == EOF){error =  10; return 10;} /* Detected EOF in the middle - output error #10*/

    if(ch != ','){error =  7; return 7;} /* Missing comma */
    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected next param */
    buffer += skip;

    if(buffer[0] == ','){error =  6; return 6;} /* Multiple consecutive commas */

    if(buffer[0] == EOF){error =  10; return 10;} /* Detected EOF in the middle - output error #10*/

    /*******************************************************/
    /* If the command is add_comp or sub_comp or mult_comp (id=2/3/6) */
    if(func_id == 2 || func_id == 3 || func_id == 6){
      var_name = buffer[0];
      for(j=0; cmpnums[j].name != '#'; j++){
        if(cmpnums[j].name == var_name){
          /* If found match for the command */
          break;
        }
      }

      if(cmpnums[j].name == '#'){
        if(var_name == ','){error = 8; return 8;} /* Illegal comma */
        return 1; /* Undefined complex variable */
      }else{
        extracted_tokens->return_param3 = cmpnums[j].cmplx;
      }

      if(buffer[1] == '\0'){error = 0; return 0;} /* If was terminated well */

      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and check if no chars at the end */
      buffer += skip;

      if(buffer[0] == EOF){error =  10; return 10;} /* Detected EOF in the middle - output error #10*/

      if(buffer[0] != '\0'){error =  5; return 5;} /* Extraneous text at end */
      error =  0; return 0;

      buffer++;
    }else{
      j=0;
      while(buffer[j] != '\0' && (isdigit((unsigned char)buffer[j]) || buffer[j] == '.' || buffer[j] == '-')){
        if(isdigit((unsigned char)buffer[j]) || buffer[j] == '-'){j++;}
        else if(buffer[j] == '.' && !dot_count){
          dot_count++;
          j++;
        }else{error = 3; return 3;} /* Invalid param - not number */
      }

      /* Convert to double */
      memcpy(partial, buffer, j);
      partial[j] = '\0';
      r = strtod(partial, &endptr); /* endptr points to the end of where the string finished parsing */

      /* Check if no number was provided to be parsed at all or if some of it wasn't parsed due to an issue in it */
      if(endptr == partial || *endptr != '\0'){error = 3; return 3;} /* Invalid param - not number */

      /* If command ended suddenly and shouldn't have*/
      if(buffer[j] == '\0' && func_id != 4 && func_id != 5){error = 4; return 4;} /* Missing param */

      if(!isdigit(buffer[j]) && buffer[j] != '\0' && (buffer[j]) != ',' && !isspace((unsigned char)buffer[j])){
        error = 3; return 3; /* Invalid param - not number */
      }

      buffer += j;
      extracted_tokens->return_param1 = r;

      /* For the second param */
      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected comma */
      buffer += skip;
      ch = buffer[0];

      /* If the command is mult_comp_real */
      if(func_id == 4 || func_id == 5){
        if(buffer[0] != '\0'){error = 5; return 5;} /* Extraneous text at end */
        error = 0; return 0;
      }
    }

    if(ch != ','){error = 7; return 7;} /* Missing comma */
    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
    buffer += skip;

    dot_count = 0;
    j=0;
    while(buffer[j] != '\0' && (isdigit((unsigned char)buffer[j]) || buffer[j] == '.' || buffer[j] == '-')){
      if(isdigit((unsigned char)buffer[j]) || buffer[j] == '-'){j++;}
      else if(buffer[j] == '.' && !dot_count){
        dot_count++;
        j++;
      }else{error =  3; return 3;} /* Invalid param - not number */
    }

    /* Convert to double */
    memcpy(partial, buffer, j);
    partial[j] = '\0';
    i = strtod(partial, &endptr);

    if(buffer[0] == '\0'){error = 4; return 4;} /* Missing parameter */

    /* If no number was parsed or if didn't finish parsing due to issue*/
    if(!isdigit(buffer[j]) && buffer[j] != '\0' && (buffer[j]) != ',' && !isspace((unsigned char)buffer[j])){
      error = 3; return 3; /* Invalid param - not number */
    }

    if(endptr == partial || *endptr != '\0'){error = 3; return 3;}  /* Invalid param - not number */

    buffer += j;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
    buffer += skip;

    if(buffer[0] != '\0'){error = 5; return 5;} /* Extraneous text at end */

    extracted_tokens->return_param2 = i;
    error = 0; return 0;
  }else{
    error = 10; return 10; /* EOF detected in buffer - terminated incorrectly */
  }
}
