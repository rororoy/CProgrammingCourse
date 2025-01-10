#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"
#include "complex.c"

int main(){
  char command[30];
  int i;
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
      }
    }
  }



  return 0;
}
