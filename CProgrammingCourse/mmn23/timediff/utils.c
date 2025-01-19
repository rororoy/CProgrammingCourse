#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "timediff.h"

int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int extract_time(int *arr, char *line){
  int i = 0;
  char *token = strtok(line, " "); /* Get the first token */
  while (token != NULL && i < 10) {
    arr[i] = atoi(token);
    token = strtok(NULL, " "); /* Get the next token */
    i++;
  }

  if(i != 10){ /* If stopped reading mid iteration */
    return 1;
  }
  return 0;
}

void build_time(int *arr ,time *t, int begin){
  int *ptr = arr + begin;
  t->date.day = *ptr++;
  t->date.month = *ptr++;
  t->date.year = *ptr++;
  t->hour.hour = *ptr++;
  t->hour.minute = *ptr++;
  t->hour.second = 0;
}

void print_time(time *t){
  printf("%d.%d.%d  ", t->date.day, t->date.month, t->date.year);
  printf("%d:%d:%d\n", t->hour.hour, t->hour.minute, t->hour.second);
}

long time_diff(time *t1, time *t2) {
    int sooner = compare_time(t1, t2);
    long days_late, days_soon;
    long seconds_late, seconds_soon;
    long total_seconds;

    if (sooner) {
        days_late = days_to_0000(t1);
        days_soon = days_to_0000(t2);
        seconds_late = seconds_to_0000(t1);
        seconds_soon = seconds_to_0000(t2);
    } else {
        days_late = days_to_0000(t2);
        days_soon = days_to_0000(t1);
        seconds_late = seconds_to_0000(t2);
        seconds_soon = seconds_to_0000(t1);
    }

    total_seconds = (days_late - days_soon) * SECONDS_IN_DAY;
    total_seconds += (seconds_late - seconds_soon);

    printf("DIFF:%ld\n", total_seconds);

    return total_seconds;
}

/*
  Given two time objects return which is sooner of the two
  Returns 0 if t1 is sooner or 1 if t2 is sooner (0 if equal)
*/
int compare_time(time *t1, time *t2){
  if (t1->date.year < t2->date.year) {
        return 0;
    } else if (t1->date.year > t2->date.year) {
        return 1;
    }

    if (t1->date.month < t2->date.month) {
        return 0;
    } else if (t1->date.month > t2->date.month) {
        return 1;
    }

    if (t1->date.day < t2->date.day) {
        return 0;
    } else if (t1->date.day > t2->date.day) {
        return 1;
    }

    if (t1->hour.hour < t2->hour.hour) {
        return 0;
    } else if (t1->hour.hour > t2->hour.hour) {
        return 1;
    }

    if (t1->hour.minute < t2->hour.minute) {
        return 0;
    } else if (t1->hour.minute > t2->hour.minute) {
        return 1;
    }

    if (t1->hour.second < t2->hour.second) {
        return 0;
    } else if (t1->hour.second > t2->hour.second) {
        return 1;
    }

    return 0; /* Equal */
}


/*
  Given a time object calculate how many seconds passed from the date to 00:00
  Return the amount of seconds (long)
*/
long seconds_to_0000(time *t){
  long total_seconds;

  total_seconds = t->hour.second; /* Extract seconds */
  total_seconds += t->hour.minute * 60; /* Minutes to 00 * 60 sec */
  total_seconds += t->hour.hour * SECONDS_IN_HOUR; /* Hours to 00 * SEC IN HOUR */

  return total_seconds;
}


/*
  Given a time object calculate how many days passed from the date to 00/00/0000
  Return the amount of days (int)
*/
long days_to_0000(time *t) {
    long total_days = 0;
    int month;

    /* Calculate days for the years */
    /* For BC years, subtract since they are before the epoch */
    if (t->date.year < 0) {
        total_days -= (abs(t->date.year)) * DAYS_IN_YEAR;
    } else {
        total_days += (t->date.year) * DAYS_IN_YEAR;
    }

    /* Calculate days for the months */
    for (month = 1; month < t->date.month; month++) {
        total_days += days_per_month[month - 1];
    }

    /* Add days */
    total_days += (t->date.day - 1); /* Subtract 1 since day starts from 1 */

    return total_days;
}
