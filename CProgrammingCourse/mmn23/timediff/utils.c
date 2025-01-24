#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "timediff.h"

/*******************************************************************************
  TODO SOLVE CALULCATION PROBLEM OF THE LAST LINE

  * Program Name: MMN 23  - utils

  * Description:
    A program with utility functions for the main timediff program

*******************************************************************************/

/* Holds number of days for each month - each index represents each month */
int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*
  Given the string type line variable from the file and the array of return vleus,
  extracts the numbers - dates and time in the format DD/MM/YYYY HH:MM:SS
  return all extracted numbers - parts of the date and hour filled in the array
  all 12 numbers extracted from the line are stored in the array
*/
int extract_time(int *arr, char *line){
  int i = 0;
  char *token = strtok(line, " "); /* Get the first token */
  while (token != NULL && i < 12) {
    arr[i] = atoi(token);
    token = strtok(NULL, " "); /* Get the next token */
    i++;
  }

  if(i != 12){ /* If stopped reading mid iteration */
    if(i == 1){return 2;} /* If read the lines and encountred an empty line */
    return 1;
  }
  return 0;
}

/*
  Given a pointer to a time type object, the array of tokanized numbers from the file
  and the index from which the return values begin which are relevant to the current:
  out of 12 numbers in the return array, only the 6 first or last represent the specific
  time we put the values into

*/
void build_time(int *arr ,time *t, int begin){
  int *ptr = arr + begin;
  t->date.year = *ptr++;
  t->date.month = *ptr++;
  t->date.day = *ptr++;
  t->hour.hour = *ptr++;
  t->hour.minute = *ptr++;
  t->hour.second = *ptr;
}

/*
  Given a pointer to a time type object prints its contents in a certain fromat:
  DD.MM.YYYY  HH:MM:SS
*/
void print_time(time *t){
  printf("%d.%d.%d  ", t->date.day, t->date.month, t->date.year);
  printf("%d:%d:%d", t->hour.hour, t->hour.minute, t->hour.second);
}

/*
  Given two pointers to a time type object
  calculates and returnes the difference between the two dates in seconds
*/
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
  Given a time object calculate how many days passed from the date to "00/00/0000":
  Assuming no year 0000 exists and year -1 goes straight to 1
  Return the amount of days (int)
*/
long days_to_0000(time *t) {
    long total_days = 0;
    int month;

    if (t->date.year < 0){
        /* BC date */
        /* Subtract (abs(year) - 1) * DAYS_IN_YEAR */
        total_days -= (abs(t->date.year) - 1) * DAYS_IN_YEAR;

        /* Subtract days remaining in the current month after the given day, inclusive */
        total_days -= (days_per_month[t->date.month - 1] - t->date.day + 1);

        /* Subtract days for the months after the current month */
        for (month = t->date.month + 1; month <= 12; month++) {
            total_days -= days_per_month[month - 1];
        }
    } else {
        /* AD date */
        /* Add (year - 1) * DAYS_IN_YEAR */
        total_days += (t->date.year - 1) * DAYS_IN_YEAR;

        /* Add days for the months before the current month */
        for (month = 1; month < t->date.month; month++) {
            total_days += days_per_month[month - 1];
        }

        /* Add days elapsed in the current month */
        total_days += (t->date.day - 1);
    }

    return total_days;
}
