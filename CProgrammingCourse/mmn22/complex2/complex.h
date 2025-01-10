#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct{
  double real;
  double img;
} complex;

extern complex A, B;

typedef struct{
  char name;
  complex *cmplx;
} cmpnums_struct;

extern cmpnums_struct cmpnums[];

#endif /* COMPLEX_H */
