#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <malloc.h>

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

#ifdef _WIN32
  while(fgets(*MEM_BUFF, _msize(*MEM_BUFF), *SRC_F) != 0) {
    fwrite(*MEM_BUFF, BEGIN_RIGHT_SPACE[lin++], 1, *TEMP_F);
    fputs("\n", *TEMP_F);

    if((*CHAR_HIT_BOTTOM) == lin) break;
  }
#elif __linux__
  while(fgets(*MEM_BUFF, malloc_usable_size(*MEM_BUFF), *SRC_F) != 0) {
    fwrite(*MEM_BUFF, BEGIN_RIGHT_SPACE[lin++], 1, *TEMP_F);
    fputs("\n", *TEMP_F);

    if((*CHAR_HIT_BOTTOM) == lin) break;
  }
#endif

  //free((int*)CHAR_HIT_BOTTOM);
  //free((char*)MEM_BUFF);
  return;
}

int __CMP__(const char* output, const char* exp_output) {

  // make sure the file formats matches with the working native systems(dos-windows, unix-linux)

  FILE * fPtr1 = fopen(output, "r");
  FILE * fPtr2 = fopen(exp_output, "r");
  if (fPtr1 == NULL || fPtr2 == NULL) {
    printf("\nUnable to open file.\n");
    printf("Please check whether file exists and you have read privilege.\n");
    exit(EXIT_FAILURE);
  }

  int ch1, ch2;
  int diff = 1;
  int f1_line = 1, f1_col = 0;

  do {
    ch1 = fgetc(fPtr1); // output file
    ch2 = fgetc(fPtr2); // expected ouput file

    // making the behaviour equivalent to diff -Z file1 file2
    if(ch1 == '\n') {
      ch1 = fgetc(fPtr1);
      f1_line += 1;
    }
    if(ch2 == '\n') {
      ch2 = fgetc(fPtr2);
    }

    if (ch1 != ch2) {
      diff -1;
      break;
    }

    f1_col += 1;

  } while (ch1 != EOF && ch2 != EOF);

  if (ch1 == EOF && ch2 == EOF)
    diff =  0;

  if (diff == 0) {
    COLOR_green(), _PASSED();
    _RESET();
  }
  else {
    printf("mismatch caught at L(%d, %d)\n", f1_line, f1_col);
    COLOR_red(), _FAILED();
    _RESET();
  }

  fclose(fPtr1);
  fclose(fPtr2);

  //free((char*)exit_output);
  //free((char*)output);

  return 0;
}
