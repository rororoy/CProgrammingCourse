#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "timediff.h"

int extract_time(int *arr, char *line){
  int dig_count = 0;
  int str_len;
  int i = 0;
  char *token = strtok(line, " "); /* Get the first token */

  while (token != NULL && i < 10) {
    if(dig_count == 5){
      dig_count = 6;
    }
    str_len = dig_count == 10 ? strlen(token) - 1 : strlen(token);
    arr[dig_count/3] = arr[dig_count/3] * (pow(10,str_len)) + atoi(token); /* Convert to integer and store */
    token = strtok(NULL, " "); /* Get the next token */
    dig_count++;
  }
  arr[1] *= 100;
  arr[3] *= 100;
  return 0;
}


int time_diff(time *t1, time *t2){
  int sooner_time;
  int year_diff;
  int month_diff;
  int day_diff;
  int month_soon;
  int month_late;
  int seconds = 0;
  int days;

  if(t1->date == t2->date){
    sooner_time = t1->hour > t2->hour ? 1 : 0;
  }else{
    sooner_time = t1->date > t2->date ? 1 : 0;
  }

  month_soon = sooner_time ? (t1->date / 10000) % 100 : t2->date / 10000) % 100;
  month_late = sooner_time ? (t2->date / 10000) % 100 : t1->date / 10000) % 100;
  year_diff = sooner_time ? t1->date % 10000 - t2->date % 10000 : t2->date % 10000 - t1->date % 10000;
  month_diff = month_soon - month_late;



  printf("YEAR DIFF: %d MONTH DIFF: %d\n", year_diff, month_diff);


  printf("SOONER:%d\n", sooner_time);
  return 0;
}
