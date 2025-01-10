#include "complex.h"

/* Define the global complex variables */
complex A = {1.0, 2.0};
complex B = {3.0, 4.0};

/* Define the cmpnums array */
cmpnums_struct cmpnums[] = {
    {'A', &A},
    {'B', &B},
    {'#', NULL}
};
