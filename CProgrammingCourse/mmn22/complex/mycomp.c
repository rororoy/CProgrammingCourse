#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"

/*
TODO print_comp and a bunch of spaces  and then A doesnt work - possibly some buffer filled
TODO handle consecutive commas
TODO handle EOF in the middle of input - should stop and error
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
        error = 2; /* Undefined command */
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
