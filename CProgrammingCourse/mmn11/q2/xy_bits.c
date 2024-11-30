#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void print_as_bin(unsigned long n);
unsigned long modify_a_bit(unsigned long x, int i);
int is_bit_on(unsigned long x, int i);

int main(){
  unsigned long x, y;
  int valid_input = 0;
  int x_bit_to_check = 13;
  int y_bit_to_check = 13;

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
  x = modify_a_bit(x, x_bit_to_check);
  printf("\nAfter turning on the %dth bit, X is now: ", x_bit_to_check);
  print_as_bin(x);
  printf("\nFor Y, is the %dth bit on?: ", y_bit_to_check);
  printf(is_bit_on(y, y_bit_to_check) ? "YES\n" : "NO\n");

  return 0;
}

/* Given an unsigned long number - print it in base 2 bit by bit */
void print_as_bin(unsigned long n){
  int i;
  for(i = sizeof(unsigned long) * 8 -1; i >= 0; i--){
    putchar((n & ((unsigned long)1 << i)) ? '1' : '0');
  }
}

/* Given an unsgined long number returns the modified number after turning on the i-th bit (counting from 0)*/
unsigned long modify_a_bit(unsigned long x, int i){
  return x |= (1<<(i-1));
}

/* Given an unsigned long number returns 1 or 0 if i-th bit is on or not */
int is_bit_on(unsigned long x, int i){
  return ((x&(1<<(i-1))) ? 1 : 0);
}
