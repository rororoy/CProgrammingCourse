#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define X_BIT_TO_CHECK 13
#define Y_BIT_TO_CHECK 7

/*******************************************************************************

  * Program Name: MMN 11 - Q2 - XY_BITS

  * Description:
    This program takes two unsigned long numbers x & y, prints and onverts them to
    base 2, turns on the 13-th bit in x and checks if 7-th bit in y is on.
    Prints results of two tasks.

  * Algorithm:
    1. Loops until valid input is entered - then outputs the input.
    2. Modify the 13-th bit of x using a function that uses a mask and an OR
    operation to turn on the bit - return the modified number.
    3. Print the new x.
    4. Check using a function if 7-th bit is on and return true/false
    5. Print accordingly YES/NO.
    6. Finish the program.

  * Input:
    Two unsigned numbers seperated by whitespace.

  * Output:
    1. Printing prompts to enter the user's input.
    2. Prints the binary representation of x and y.
    3. Prints the modified x number in binary and then in dec.
    4. Prints YES/NO if the 7-th bit was on in y.
    * For every print there are explenation sentences that come before the output.

  * Notes:
    Eample input tests can be found in the same directory as this program.

*******************************************************************************/

void print_as_bin(unsigned long n);
unsigned long modify_a_bit(unsigned long x, int i);
int is_bit_on(unsigned long x, int i);

int main(){
  unsigned long x, y; /* Our two input numbers */
  int valid_input = 0; /* Is set to true/1 when valid input was entered */

  printf("Enter your two numbers X and Y:\n");

  /* Read the input and check for validity */
  while(!valid_input){
    if(scanf("%lu %lu", &x, &y) == 2){
      /* If valid: prints input */
      printf("You've entered X = ");
      print_as_bin(x);
      printf("\nYou've entered Y = ");
      print_as_bin(y);
      valid_input = 1;
    }else{
      /* If not valid: print error and clear invalid chars in buffer */
      printf("Invalid input. Please input two unsigned long numbers.\n");

       /* Clear input buffer */
      while(getchar() != '\n'){
        /* Discards the invalid charachters */
      }
    }
  }

  /* Calculate and print results */
  x = modify_a_bit(x, X_BIT_TO_CHECK);
  printf("\nAfter turning on the %dth bit, X is now: ", X_BIT_TO_CHECK);
  print_as_bin(x);
  printf("\nFor Y, is the %dth bit on?: ", Y_BIT_TO_CHECK);
  printf(is_bit_on(y, Y_BIT_TO_CHECK) ? "YES\n" : "NO\n ");

  return 0;
}

/*
  Given an unsigned long number - print it in base 2 bit by bit
  Starting from MSB, iterate through all bits of n in base 2, for each bit position create
   a mask usign shift left to isolate the bit (AND gate). Print 1 or 0 representing the
   state of the bit.
*/
void print_as_bin(unsigned long n){
  int i;
  for(i = sizeof(unsigned long) * 8 -1; i >= 0; i--){
    putchar((n & ((unsigned long)1 << i)) ? '1' : '0'); /* Algo explenation above */
  }
  /* Prints also representation in base10 */
  printf("   (=%lu)", n);
}

/*
  Given an unsgined long number returns the modified number after turning on the i-th bit (counting from 0)
*/
unsigned long modify_a_bit(unsigned long x, int i){
  return x |= (1<<(i-1)); /* Create a mask for the i-th bit (000...010...0) that turns it on and return the result. */
}

/*
  Given an unsigned long number returns 1 or 0 if i-th bit is on or not
*/
int is_bit_on(unsigned long y, int i){
  return ((y&(1<<(i-1))) ? 1 : 0); /* 1 if y AND (000...00100...0) isn't equal (0)dec, return 0 otherwise (mask filter for 7th bit). */
}
