#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024 /* Maximum line length buffer to read at a time */
#define SECONDS_IN_DAY 86400
#define DAYS_IN_YEAR 365

typedef struct{
  int date;
  int hour;
} time;

int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Function to compare two time objects and return the bigger of the two */
time *compare_time(time *t1, time *t2);

/* Given a time object print it in a format */
void print_time(time *t);

/* Given two time objects calculate the difference between them, return amount of seconds between */
int time_diff(time *t1, time *t2);

int extract_time(int *arr, char *line);
