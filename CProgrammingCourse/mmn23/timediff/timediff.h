#ifndef TIMEDIFF_H
#define TIMEDIFF_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024 /* Maximum line length buffer to read at a time */
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define DAYS_IN_YEAR 365

typedef struct{
  int date;
  int hour;
} time;

extern int days_per_month[];
/* Function to compare two time objects and return the bigger of the two */
time *compare_time(time *t1, time *t2);

/* Given a time object print it in a format */
void print_time(time *t);

/* Given two time objects calculate the difference between them, return amount of seconds between */
long long time_diff(time *t1, time *t2);

int extract_time(int *arr, char *line);

int days_to_0000(time *t);

int seconds_to_0000(time *t);

#endif /* TIMEDIFF_H */
