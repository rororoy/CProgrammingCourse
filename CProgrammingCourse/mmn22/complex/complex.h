#ifndef COMPLEX_H
#define COMPLEX_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 100

/* Define the complex number type with real=x, img=y to represent n = x+iy */
typedef struct{
  double real;
  double img;
} complex;

/* Define our complex number vars A-F */
extern complex A, B, C, D, E, F;

typedef struct{
  int error_code;
  char error_msg[50];
} errors_struct;

/* Define a database of possible varaibles user can use */
typedef struct{
  char name;
  complex *cmplx;
} cmpnums_struct;

typedef struct{
  complex *target;
  int func_id;
  double return_param1;
  double return_param2;
  complex *return_param3;
} tokenized;

int tokenize_input(tokenized *extracted_tokens);

void read_comp(void);

void print_comp(void);

void print_comp_internal(complex *comp);

void add_comp(void);

void sub_comp(void);

void mult_comp_real(void);

void mult_comp_img(void);

void mult_comp_comp(void);

void abs_comp(void);

int stop();

/* Define a command database with pointers to functions for each valid command */
typedef struct{
  char *name;
  void (*func)(void);
} cmd_struct;

extern cmpnums_struct cmpnums[];
extern cmd_struct cmd[];
extern errors_struct errors[];

#endif /* COMPLEX_H */
