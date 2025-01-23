#ifndef TIMEDIFF_H
#define TIMEDIFF_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024 /* Maximum line length buffer to read at a time */
/* Time constants: */
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define DAYS_IN_YEAR 365

/* dates object representing a date inthe format DD.MM.YYYY */
typedef struct{
  int day;
  int month;
  int year;
} dates;

/* hours object representing an hour in the format HH:MM:SS */
typedef struct{
  int hour;
  int minute;
  int second;
} hours;

/* time object representing a date and specific hour */
typedef struct{
  dates date;
  hours hour;
} time;

extern int days_per_month[];

int compare_time(time *t1, time *t2);

void build_time(int *arr ,time *t, int begin);

void print_time(time *t);

long time_diff(time *t1, time *t2);

int extract_time(int *arr, char *line);

long days_to_0000(time *t);

long seconds_to_0000(time *t);

#endif /* TIMEDIFF_H */
