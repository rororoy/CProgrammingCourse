#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timediff.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  char line[MAX_LINE_LENGTH]; /* Buffer to hold each line */

  /* Check if a file name is provided as an argument */
  if (argc != 2) {
      fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
      return 1;
  }

  /* Open the file for reading */

  file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(line, sizeof(line), file) != NULL) {
    int return_args[12];
    int input_error;
    long seconds;
    time t1, t2;
    input_error = extract_time(return_args, line);

    if(input_error){break;}

    build_time(return_args, &t1, 0);
    build_time(return_args, &t2, 6);


    seconds = time_diff(&t1, &t2);
    printf("Calculated difference in seconds between: ");

    if(compare_time(&t1,&t2)){ /* If t2 is sooner */
      print_time(&t1);
      printf(" and ");
      print_time(&t2);
    }else{
      print_time(&t2);
      printf("   and   ");
      print_time(&t1);
    }
    printf(" --> %ld seconds\n", seconds);
  }

    /* Check for reading errors */
  if (ferror(file)) {
      perror("Error reading file");
  }



  /* Close the file */
  fclose(file);
  return 0;
}
