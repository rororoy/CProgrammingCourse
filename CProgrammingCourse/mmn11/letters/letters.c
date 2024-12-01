#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 100 /* The size of the buffer we use for the quote storage */

/*******************************************************************************

  * Program Name: MMN 11 - Q1 - LETTERS

  * Description:
    This program takes a prompt of multiple sentences. It modifies the input and prints it to fit certain rules:
    1. At the start of every new sentence the first char should be uppercase.
    2. Between quotation marks - all text should be in uppercase.
    3. For every other case the text should be in lowercase.
    4. Don't print any numbers, symbols are ok.

  * Algorithm:
    1. Loops until EOF - handles one char entered at a time.
    2. Holds two states of the program - if encountered a dot and if currently inside quotes.
    3. First checks if the char is a dot - if yes, skip the loop to the next char.
    4. If char is a digit - do nothing and end loop, otherwise continue with the checks.
    5. If encountered a quotation mark check if were in the quote or starting a new one.
    6. If we passed the start of the new quote - use buffer quote_store to store the chars
       to later decide what to do with.
    7. If were at the end of a quote (based on the state variable) print everything saved
       in the buffer as upper case and clear the buffer (by resetting the index pointer that
       points past the last char saved).
    8. If the char isn't a quote and were not inside the quote, check if were at the start of
    a new sentence and char isnt a whitespace and print the relevent char in uppercase.
    9. Finally if all checks didn't pass then were looking at a regular case for the char that should be
    printed in lowercase
    10. Loop ends and we take another char from the user.
    11. After EOF and the loops end - look at if our state was inside a quote that didn't close before EOF.
        if that's the case we need to print the chars in the storage buffer all in lower.

  * Input:
    A sentence / paragraph

  * Output:
    The modified text to fit the rules.

  * Notes:
    Eample input tests can be found in the same directory as this program.

*******************************************************************************/


int main(){

  char ch;
  int end_sentence = 1;
  int inside_quotes = 0;
  char quote_store[BUFFER_SIZE]; /* Stores sentences inside the quotes to handle end of quote (buffer) */
  int quote_i = 0; /* Pointer for the quote_store arr - if last char is i, points to i+1 */
  int i; /* Temp counter */

  printf("Enter your input (ctrl-D to finish typing):\n");

  while((ch=getchar())!= EOF){
    if(!inside_quotes){ /* Detects and handles end of sentene except when in quotes */
      if(ch == '.'){
        end_sentence = 1;
        putchar(ch);
        continue; /* If we've encountered a dot no need to further check, continue to next char */
        }
      }

    if(!isdigit(ch)){ /* Only if the char isnt a digit handle it - else will skip it to the next char*/
      if(ch == '"'){
        inside_quotes = !inside_quotes;
        if(!inside_quotes){ /* If just left quotes - print all in upper */
          for(i = 0; i < quote_i; i++){
            putchar(toupper(quote_store[i]));
          }
          putchar(ch); /* Then print the " itself */
          quote_i = 0; /* Reanitilize the quote_store arr */
          quote_store[0] = '\0';
        }else{ /* If quote started simply print -> " */
          putchar(ch);
        }
      }else{
        if(inside_quotes){
          quote_store[quote_i] = tolower(ch); /* Store the sentence inside the quotes to later decide what to do with */
          quote_i++;
        }else{
          if(end_sentence && !isspace(ch)){ /* Handle first char of new sentence thats not a whitespace */
            end_sentence = 0;
            putchar(toupper(ch));
          }else{ /* At any other case (the default) just print the char */
            putchar(tolower(ch));
          }
        }
      }
    }
  }

  if(inside_quotes){ /* If reached EOF (input endeed) while still in quotes - retroactivly print all storage */
    quote_store[quote_i] = '\0'; /* Mark arr end with null char before printing */
    printf("%s\n", quote_store);
  }

  return 0;
}
