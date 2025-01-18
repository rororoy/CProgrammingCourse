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
    int return_args[4] = {0,0,0,0};
    int input_error;
    long long seconds;
    time t1, t2;
    input_error = extract_time(return_args, line);

    if(input_error){break;}

    printf("GOT ERROR:%d\n", input_error);
    printf("GOT NUMBER: %d, %d, %d, %d\n", return_args[0], return_args[1], return_args[2], return_args[3]);
    t1.date = return_args[0];
    t1.hour = return_args[1];
    t2.date = return_args[2];
    t2.hour = return_args[3];

    seconds = time_diff(&t1, &t2);
  }

    /* Check for reading errors */
  if (ferror(file)) {
      perror("Error reading file");
  }



  /* Close the file */
  fclose(file);
  return 0;
}
