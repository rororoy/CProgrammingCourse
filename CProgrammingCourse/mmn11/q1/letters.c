#include <stdio.h>
#include <string.h>
#include <ctype.h>

char quote_handler(int inside_quotes);

int main(){

  char ch;
  int end_sentence = 1;
  int inside_quotes = 0;
  char quote_store[100]; /* Stores sentences inside the quotes to handle end of quote (buffer) */
  int quote_i = 0; /* Pointer for the quote_store arr */
  int i; /* Temp counter */

  printf("Enter your input (ctrl-D to finish typing):\n");

  while((ch=getchar())!= EOF){
    if(!inside_quotes){ /* Detects and handles end of sentene except when in quotes */
      if(ch == '.'){
        end_sentence = 1;
        putchar(ch);
        continue;
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
      quote_store[quote_i+1] = '\0'; /* Mark arr end with null char before printing */
    printf("%s\n", quote_store);
  }

  return 0;
}
