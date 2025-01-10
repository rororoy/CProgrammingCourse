#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"

/*
TODO rewrite the tokenizer to return only ints no printing
TODO move the defenition of the tokenized object to the main func
TODO think how to pass back the error code
TODO switch buffer to malloc
*/

/* Define the global complex variables */
complex A = {0.0, 0.0};
complex B = {0.0, 0.0};
complex C = {0.0, 0.0};
complex D = {0.0, 0.0};
complex E = {0.0, 0.0};
complex F = {0.0, 0.0};

int main(){
  char command[30];
  int i;

  printf("Initialized complex numbers A-F to default values of 0+0i\n");
  printf("Please enter a valid command out of possible commands:\n");
  for(i=0; cmd[i].func != NULL; i++){
    printf("%s ", cmd[i].name);
  }
  printf("\n\n");

  for(;;){
    if(scanf("%s", command) == 1){
      for(i=0; cmd[i].func != NULL; i++){
        if(strcmp(command, cmd[i].name)==0){
          /* If found match for the command */
          break;
        }
      }

      if(cmd[i].func == NULL){
        printf("\nUndefined command name\n");
      }else{
        (*(cmd[i].func))();
        /* Check for passed error from the functions */
        if(error != 0){
          printf("\nERROR %d\n", error);
        }
        /*printf("\nComplex A: %2f+i%2f\n", A.real, A.img);*/
      }
    }
  }



  return 0;
}
