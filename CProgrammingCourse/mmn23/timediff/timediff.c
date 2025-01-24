#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timediff.h"

#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
  TODO SOLVE CALULCATION PROBLEM OF THE LAST LINE

  * Program Name: MMN 23  - TIME DIFFERENCE

  * Description:
    This program reads lines from a given file, for each line of expected 12 numbers:
    6 for each time: 3 for the date and 3 for the hour: DD.MM.YYYY HH:MM:SS
    it extracts the numbers and builds two time objects and prints and calculates in
    seconds the difference in seconds between the two times

  * Variables and data structures:
      1. time object defined in the header file: containes two objects: month and date
      2. months object contains and representing in 3 numbers a date: DD.MM.YYYY
      3. hours object contains and representing in 3 numbers an hour: HH:MM:SS
      4. days per month: stores number of days in each month in an array, each
      index holds the days of that month(minus 1 ==> 0 is jan...)

    * Algorithm:
      1. Validates command structures by scanning the passed additional arguments
      2. Reads the file passed line by line
      3. for each line containing 12 numbers representing two time objects:
      4. extract the input and build the two time objects
      5. calculate the difference between the two time objects in the time_diff function
        - does so by finding out which time is sooner
        - for each time calculates how many days passed from the date to the end of the epoch (00/00/0000)
        - when its known there is no year 0 between years 1 and -1
        - converts the days to an amount of seconds difference
        - for each hour of a time calcualtes the seconds passed from 00:00
        - adds the two results for each time, calculates the difference between the two results,
         the later time minus the sooner
         - returns the result
      6. prints the result


    * Input:
      Commands in the format ./timediff <filename>
      Format of the time in the file for each line: DD MM YY HH MM SS DD MM YY HH MM SS --> <time #1> <time #2>

    * Output:
      Prints the difference between the two dates in each line in seconds

    * Notes:
      Eample input tests can be found in the same directory as this program. See README.
      Assumes input is valid and no need to check for validity inside file

*******************************************************************************/



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

  /* loop throguh each line of the file */
  while (fgets(line, sizeof(line), file) != NULL) {
    int return_args[NUMBERS_PER_LINE];
    int input_error;
    long seconds;
    time t1, t2;
    input_error = extract_time(return_args, line);

    if(!input_error){ /* if no error encountred */
      /* build each time object using the array of tokanized numbers for each line */
      /* in the array of 12 (=NUMBERS_PER_LINE) numbers,
      the first hald represents the first number and the other the seconds one */
      build_time(return_args, &t1, 0);
      build_time(return_args, &t2, NUMBERS_PER_LINE/2);


      seconds = time_diff(&t1, &t2);

      /* Printing based on what time is later - first print later then sooner */
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
    }else if(input_error != 2){ /* Error 2 is saved for times when an empty line is encountered */
      printf("Error encountered %d\n", input_error);
    }
  }

    /* Check for reading errors */
  if (ferror(file)) {
      perror("Error reading file");
  }

  /* Close the file */
  fclose(file);
  return 0;
}
