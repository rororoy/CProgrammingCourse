#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

int error;

/* Define the cmpnums array */
cmpnums_struct cmpnums[] = {
    {'A', &A},
    {'B', &B},
    {'C', &C},
    {'D', &D},
    {'E', &E},
    {'F', &F},
    {'#', NULL} /* Marks the end */
};

/* Define the cmd array */
cmd_struct cmd[] = {
    {"read_comp", read_comp},
    {"print_comp", print_comp},
    {"add_comp", add_comp},
    {"sub_comp", sub_comp},
    {"mult_comp_real", mult_comp_real},
    {"mult_comp_img", mult_comp_img},
    {"mult_comp_comp", mult_comp_comp},
    {"abs_comp", abs_comp},
    {"stop", stop},
    {"not_valid", NULL}
  };

errors_struct errors[] = {
  {0, "OK"},
  {1, "Undefined complex variable"},
  {2, "Undefined command name"},
  {3, "Invalid parameter - not a number"},
  {4, "Missing parameter"},
  {5, "Extraneous text after end of command"},
  {6, "Multiple consecutive commas"},
  {7, "Missing comma"},
  {8, "Illegal comma"},
  {9, "Program terminated"},
  {10, "Program terminated incorrectly - use stop"}
};

/*
cmd_struct cmd[] = {
}; */

void read_comp(void){
  tokenized extracted_tokens = {NULL, 0, 0, 0, NULL}; /* read_comp id is 0 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real = extracted_tokens.return_param1;
    extracted_tokens.target->img = extracted_tokens.return_param2;
  }
}

void print_comp(void){
  tokenized extracted_tokens = {NULL, 1, 0, 0, NULL}; /* print_comp id is 1 */
  if(!(error = tokenize_input(&extracted_tokens))){
    print_comp_internal(extracted_tokens.target);
  }
}

/* Internal complex print */
void print_comp_internal(complex *comp){
  if(comp->img < 0){
    printf("%.2f - (%.2f)i\n",comp->real, fabs(comp->img));
  }else{
    printf("%.2f + (%.2f)i\n",comp->real, comp->img);
  }
}

void add_comp(void){
  tokenized extracted_tokens = {NULL, 2, 0, 0, NULL}; /* add_comp id is 2 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real += extracted_tokens.return_param3->real;
    extracted_tokens.target->img += extracted_tokens.return_param3->img;
    print_comp_internal(extracted_tokens.target);
  }
}

void sub_comp(void){
  tokenized extracted_tokens = {NULL, 3, 0, 0, NULL}; /* add_comp id is 3 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real -= extracted_tokens.return_param3->real;
    extracted_tokens.target->img -= extracted_tokens.return_param3->img;
    print_comp_internal(extracted_tokens.target);
  }
}


void mult_comp_real(void){
  tokenized extracted_tokens = {NULL, 4, 0, 0, NULL}; /* mult_comp_real id is 4 */
  if(!(error = tokenize_input(&extracted_tokens))){
    extracted_tokens.target->real *= extracted_tokens.return_param1;
    extracted_tokens.target->img *= extracted_tokens.return_param1;
    print_comp_internal(extracted_tokens.target);
  }
}

void mult_comp_img(void){
  tokenized extracted_tokens = {NULL, 5, 0, 0, NULL}; /* mult_comp_real id is 4 */
  if(!(error = tokenize_input(&extracted_tokens))){
    int temp_real = extracted_tokens.target->real;
    extracted_tokens.target->real = -(extracted_tokens.return_param1 * extracted_tokens.target->img);
    extracted_tokens.target->img = extracted_tokens.return_param1 * temp_real;
    print_comp_internal(extracted_tokens.target);
  }
}

void mult_comp_comp(void){
  tokenized extracted_tokens = {NULL, 6, 0, 0, NULL}; /* mult_comp_comp id is 6 */
  if(!(error = tokenize_input(&extracted_tokens))){
    /* (a+bi)*(c+di) = (ac-bd)+(ad+bc)i */
    int temp_real = extracted_tokens.target->real;
    extracted_tokens.target->real = (extracted_tokens.target->real * extracted_tokens.return_param3->real) - (extracted_tokens.target->img * extracted_tokens.return_param3->img);
    extracted_tokens.target->img = (temp_real * extracted_tokens.return_param3->img) + (extracted_tokens.target->img * extracted_tokens.return_param3->real);
    print_comp_internal(extracted_tokens.target);
  }
}

void abs_comp(void){
  tokenized extracted_tokens = {NULL, 7, 0, 0, NULL}; /* abc_comp id is 7 */
  if(!(error = tokenize_input(&extracted_tokens))){
    double calculated_abs = sqrt((extracted_tokens.target->real*extracted_tokens.target->real) + (extracted_tokens.target->img*extracted_tokens.target->img));
    printf("%.2f\n", (calculated_abs));
  }
}

void stop(void){
  int skip;
  char actual_buffer[100];
  char *buffer = actual_buffer;
  char ch;

  /* Get the rest of the command from stdin and store in a buffer */
  if(fgets(actual_buffer, sizeof(actual_buffer), stdin) != NULL){
    int len = strlen(actual_buffer);
    if(len>0 && actual_buffer[len-1] == '\n'){
      /* Strip nl char at the end of the input */
      actual_buffer[len-1] = '\0';
    }

    /* Extract first non whitespace char */
    skip = strspn(actual_buffer, " \t\r\n"); /* Skip whitespace and get first param */
    buffer += skip;
    ch = buffer[0];

    /* check if command has extraneous text at the end */
    if(ch != '\0'){error = 5;} /* Extraneous text at the end */
    else{error = 9;} /* Program terminated */
  }
}

/* Gets the input from the user, handles it and returns all the params it extracted and the error code */
int tokenize_input(tokenized *extracted_tokens){
  char var_name;
  double r, i;
  int skip;
  char ch;
  char partial[50];
  int j = 0; /* Iterator */
  int dot_count=0;
  char actual_buffer[100];
  char *buffer = actual_buffer;
  char *endptr;
  int func_id = extracted_tokens->func_id;

  /* Get the rest of the command from stdin and store in a buffer */
  if(fgets(actual_buffer, sizeof(actual_buffer), stdin) != NULL){
    int len = strlen(actual_buffer);
    if(feof(stdin)){return 10;}
    if(len>0 && actual_buffer[len-1] == '\n'){
      /* Strip nl char at the end of the input */
      actual_buffer[len-1] = '\0';
    }

    /* Extract var_name */
    skip = strspn(actual_buffer, " \t\r\n"); /* Skip whitespace and get first param */
    buffer += skip;
    var_name = buffer[0];

    if(var_name == EOF){return 10;} /* Detected EOF in the middle - output error #10*/

    for(j=0; cmpnums[j].name != '#'; j++){
      if(cmpnums[j].name == var_name){
        /* If found match for the command */
        break;
      }
    }

    if(cmpnums[j].name == '#'){
      if(var_name == ','){return 8;} /* Illegal comma */
      if(func_id == 1 || func_id == 7){return 4;}
      return 1; /* Undefined complex var */
    }else{
      extracted_tokens->target = cmpnums[j].cmplx;
    }

    /*******************************************************/
    /* If the command is print_comp (id=1) or abs_comp (id=7) */
    if(func_id == 1 || func_id == 7){
      if(buffer[1] == '\0'){return 0;} /* If was terminated well */

      buffer += 1;

      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
      buffer += skip;

      if(buffer[0] == EOF){return 10;} /* Detected EOF in the middle - output error #10*/

      if(buffer[0] != '\0'){return 5;} /* Extraneous text at end */
      return 0;
    }

    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected comma */
    buffer += skip;
    ch = buffer[0];

    if(buffer[0] == EOF){return 10;} /* Detected EOF in the middle - output error #10*/

    if(ch != ','){return 7;} /* Missing comma */
    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected next param */
    buffer += skip;

    if(buffer[0] == EOF){return 10;} /* Detected EOF in the middle - output error #10*/

    /*******************************************************/
    /* If the command is add_comp or sub_comp or mult_comp (id=2/3/6) */
    if(func_id == 2 || func_id == 3 || func_id == 6){
      var_name = buffer[0];
      for(j=0; cmpnums[j].name != '#'; j++){
        if(cmpnums[j].name == var_name){
          /* If found match for the command */
          break;
        }
      }

      if(cmpnums[j].name == '#'){
        if(var_name == ','){return 8;} /* Illegal comma */
        return 1; /* Undefined complex variable */
      }else{
        extracted_tokens->return_param3 = cmpnums[j].cmplx;
      }

      if(buffer[1] == '\0'){return 0;} /* If was terminated well */

      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and check if no chars at the end */
      buffer += skip;

      if(buffer[0] == EOF){return 10;} /* Detected EOF in the middle - output error #10*/

      if(buffer[0] != '\0'){return 5;} /* Extraneous text at end */
      return 0;

      buffer++;
    }else{
      j=0;
      while(buffer[j] != '\0' && (isdigit((unsigned char)buffer[j]) || buffer[j] == '.' || buffer[j] == '-')){
        if(isdigit((unsigned char)buffer[j]) || buffer[j] == '-'){j++;}
        else if(buffer[j] == '.' && !dot_count){
          dot_count++;
          j++;
        }else{return 3;} /* Invalid param - not number */
      }

      /* Convert to double */
      memcpy(partial, buffer, j);
      partial[j] = '\0';
      r = strtod(partial, &endptr); /* endptr points to the end of where the string finished parsing */

      /* Check if no number was provided to be parsed at all or if some of it wasn't parsed due to an issue in it */
      if(endptr == partial || *endptr != '\0'){return 3;} /* Invalid param - not number */

      /* TODO check this */
      if(!isdigit(buffer[j]) && buffer[j] != '\0' && (buffer[j]) != ',' && !isspace((unsigned char)buffer[j])){
        return 3; /* Invalid param - not number */
      }

      /* If command ended suddenly and shouldn't have*/
      if(buffer[j] == '\0' && func_id != 4 && func_id != 5){return 4;} /* Missing param */

      buffer += j;
      extracted_tokens->return_param1 = r;

      /* For the second param */
      skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected comma */
      buffer += skip;
      ch = buffer[0];

      /* If the command is mult_comp_real */
      if(func_id == 4 || func_id == 5){
        if(buffer[0] != '\0'){return 5;} /* Extraneous text at end */
        return 0;
      }
    }

    if(ch != ','){return 7;} /* Missing comma */
    buffer++;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
    buffer += skip;

    dot_count = 0;
    j=0;
    while(buffer[j] != '\0' && (isdigit((unsigned char)buffer[j]) || buffer[j] == '.' || buffer[j] == '-')){
      if(isdigit((unsigned char)buffer[j]) || buffer[j] == '-'){j++;}
      else if(buffer[j] == '.' && !dot_count){
        dot_count++;
        j++;
      }else{return 3;} /* Invalid param - not number */
    }

    /* Convert to double */
    memcpy(partial, buffer, j);
    partial[j] = '\0';
    i = strtod(partial, &endptr);

    /* If no number was parsed or if didn't finish parsing due to issue*/
    if(endptr == partial || *endptr != '\0'){return 3;}  /* Invalid param - not number */

    buffer += j;

    skip = strspn(buffer, " \t\r\n"); /* Skip whitespace and get to expected double */
    buffer += skip;

    if(buffer[0] != '\0'){return 5;} /* Extraneous text at end */

    extracted_tokens->return_param2 = i;
    return 0;
  }else{
    printf("test\n");
    return 10; /* EOF detected in buffer - terminated incorrectly */
  }
}
