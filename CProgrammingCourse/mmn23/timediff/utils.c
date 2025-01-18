#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "timediff.h"

int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int extract_time(int *arr, char *line){
  int dig_count = 0;
  int str_len;
  int i = 0;
  char *token = strtok(line, " "); /* Get the first token */

  while (token != NULL && i < 10) {
    if(dig_count == 5){
      dig_count++;
    }

    /* If looking at the day or month make sure it is saved as two digits */
    if(dig_count == 0 || dig_count == 1 || dig_count == 6 || dig_count == 7){
      str_len = 2;
    }else{
      str_len = dig_count == 10 ? strlen(token) - 1 : strlen(token);
    }

    if(atoi(token) < 0 && (dig_count == 8 || dig_count == 2)){ /* For negative years */
      arr[dig_count/3] = arr[dig_count/3] * (pow(10,str_len-1)) + (abs(atoi(token))); /* Incase of a negative year add an offest of 9000 to it */
      arr[dig_count/3] *= -1;
    }else{
      arr[dig_count/3] = arr[dig_count/3] * (pow(10,str_len)) + atoi(token); /* Convert to integer and store */
    }
    token = strtok(NULL, " "); /* Get the next token */
    dig_count++;
  }
  arr[1] *= 100;
  arr[3] *= 100;
  return 0;
}


long long time_diff(time *t1, time *t2){
  int sooner_time;
  long long seconds;
  int total_days_soon, total_days_late; /* Total days since 0000 */
  int seconds_soon, seconds_late;

  if(t1->date == t2->date){
    sooner_time = t1->hour > t2->hour ? 1 : 0;
  }else{
    sooner_time = t1->date > t2->date ? 1 : 0;
  }

  total_days_late = sooner_time ? days_to_0000(t1) : days_to_0000(t2);
  total_days_soon = !sooner_time ? days_to_0000(t1) : days_to_0000(t2);

  seconds_soon = sooner_time ? seconds_to_0000(t1) : seconds_to_0000(t2);
  seconds_late = !sooner_time ? seconds_to_0000(t1) : seconds_to_0000(t2);

  seconds = (total_days_late-total_days_soon) * SECONDS_IN_DAY;
  seconds += seconds_late - seconds_soon;

  printf("SOONER:%d\n", sooner_time);
  printf("TIME DIFF %d - %d: %d\n", total_days_late, total_days_soon, total_days_late-total_days_soon);
  printf("SECONDS DIFF %d\n\n", seconds);


  return seconds;
}

int days_to_0000(time *t){
  int total_days;
  int month, year;

  total_days = abs((t->date / 1000000) % 100);
  month = (t->date / 10000) % 100;
  for(month=abs(month)-1; month > 0; month--){
    total_days += days_per_month[month-1];
  }

  year = t->date % 10000;
  total_days += abs(year) * DAYS_IN_YEAR;
  if(year < 0){ /* For dates before the year 0000 save the days as negative */
    total_days *= -1;
  }
  printf("FOR DATE: %d GOT DAYS: %d\n", t->date, total_days);
  return total_days;
}

int seconds_to_0000(time *t){
  int total_seconds;

  total_seconds = t->hour % 100; /* Extract seconds */
  total_seconds += ((t->hour / 100) % 100) * 60; /* Minutes to 00 * 60 sec */
  total_seconds += t->hour / 10000; /* Hours to 00 * SEC IN HOUR */

  return total_seconds;

}
