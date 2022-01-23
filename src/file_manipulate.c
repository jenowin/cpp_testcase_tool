#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int BEGIN_RIGHT_SPACE[100]={0};

bool is_EMPTY_LINE(const char *str) {
  char ch;
  do {
    ch = *(str++);
    if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0') return 0;

  } while (ch != '\0');
  //free((char*)str);
  return 1;
}

void WRITE_FILE(FILE** const SRC_F, FILE** const TEMP_F, const int* CHAR_HIT_BOTTOM, char** const MEM_BUFF) {
  if(*CHAR_HIT_BOTTOM == 0) return;
  int lin = 0;
  while(fgets(*MEM_BUFF, _msize(*MEM_BUFF), *SRC_F) != 0) {
    fwrite(*MEM_BUFF, BEGIN_RIGHT_SPACE[lin++], 1, *TEMP_F);
    fputs("\n", *TEMP_F);

    if((*CHAR_HIT_BOTTOM) == lin) break;
  }
  fclose(*SRC_F);
  fclose(*TEMP_F);
  //free((int*)CHAR_HIT_BOTTOM);
  //free((char*)MEM_BUFF);
  return;
}

int __CMP__(const char* input, const char* output) {
  FILE * fPtr1;
  FILE * fPtr2;
  int diff;
  int line, col;
  fopen_s(&fPtr1, input, "r");
  fopen_s(&fPtr2, output, "r");

  if (fPtr1 == NULL || fPtr2 == NULL) {
    printf("\nUnable to open file.\n");
    printf("Please check whether file exists and you have read privilege.\n");
    exit(EXIT_FAILURE);
  }

  int ch1, ch2;

  //line = 1;
  //col  = 0;

  do {
    ch1 = fgetc(fPtr1);
    ch2 = fgetc(fPtr2);

    /*
    if (ch1 == '\n') {
      line += 1;
      col = 0;
    }
    */

    if (ch1 != ch2) {
      diff -1;
      break;
    }

    // col += 1;

  } while (ch1 != EOF && ch2 != EOF);

  //strange behaviour in file after stream(>) using cmd in windows.
  //due to that reason file which is streamed using oper(>) should be interated once more.
  ch1 = fgetc(fPtr1);
  //ch2 = fgetc(fPtr2);

  if (ch1 == EOF && ch2 == EOF)
    diff =  0;
  else
    diff = -1;


  if (diff == 0) {
    COLOR_green(), _PASSED();
    _RESET();
  }
  else {
    COLOR_red(), _FAILED();
    _RESET();
  }

  fclose(fPtr1);
  fclose(fPtr2);

  //free((char*)input);
  //free((char*)output);
  return 0;
}
