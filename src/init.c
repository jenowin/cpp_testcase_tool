#include<sys/time.h>
#include<string.h>
#include "ansi_colors.h"
#include "__commence.c"
#include "memory_calc.h"

char CC[2] = "14";
void file_COMPILE(const int* ARG_cnt, const char* test, const char* fname){
  char commands[380];

#ifdef _WIN32
  sprintf(commands, "g++ -std=c++%s -O2 -g -Wall -Wshadow \"-Wl,--stack=268435456\" -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion  -fno-sanitize-recover=all -fstack-protector-all -D FORTIFY_SOURCE=2  -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -o %s %s.cpp", CC, fname, fname);
#elif __linux__
  sprintf(commands, "g++ -std=c++%s -O2 -g -Wall -Wshadow -Wl -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -fsanitize=address -fsanitize-undefined -fsanitize-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all -fstack-protector-all -D FORTIFY_SOURCE=2  -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -o %s %s.cpp", CC, fname, fname);
#endif

  printf("Compiling %s.cpp with c++%s.\n", fname, CC);

  test ? printf("Running test - %s\n", test) : 0;
  if (!system(commands)) {
    COLOR_green(), EXIT_CODE_ZERO();
    _RESET();
    DISPLAY_MEM_SRC_EXE(fname);
  } else {
    COLOR_red(), EXIT_CODE_ONE();
    _RESET(), exit(EXIT_FAILURE);
  }
  return;
}

void UPDATE_OUTP(const char* exec_fname, const char* IN, const char* OP) {
  char cmd[20];
  char new_l[20];
  //sprintf(cmd, "%s<%s>%s", fname, IN, OP);

#ifdef _WIN32
  sprintf(cmd, "%s<%s>%s", exec_fname, IN, OP);
  system(cmd);

  //(echo.) >> output,  append new line(windows) at the end of file.
  //sprintf(new_l, "(echo.) >> %s", OP);
  //system(new_l);

  return;
#elif __linux__
  sprintf(cmd, "./%s<%s > %s", exec_fname, IN, OP);
  system(cmd);

  //./%s<%s>%s No new line created.
  // echo $(./%s<%s) > output, creates new line(linux).
  //sprintf(cmd, "echo $(./%s<%s) > %s", exec_fname, IN, OP);
  //system(cmd);

  return;
#endif

}

void DISPLAY_EXPECTED_OUTPUT(const char* op, const char* exp_op) {
  char cmd[15];

  printf("Output:\n");
  sprintf(cmd, "cat %s", op);
  system(cmd);
  printf("\n____________________________\n");

  memset(cmd, 0, sizeof cmd);

  printf("Expected:\n");
  sprintf(cmd, "cat %s", exp_op);
  system(cmd);
  printf("\n____________________________\n");
  return;
}

void DIS_END_TIME(struct timeval *begin, struct timeval *end) {
  gettimeofday(&(*end), 0);
  long seconds = (*end).tv_sec - (*begin).tv_sec;
  long microseconds = (*end).tv_usec - (*begin).tv_usec;
  double elapsed = seconds + microseconds*1e-6;
  printf("Time: %.3fs\n", elapsed);
  return;
}

int main (int argc, char* argv[]) {

  struct timeval begin, end;
  gettimeofday(&begin, 0);

  switch(argc) {
  case 1:
    printf("No arguments argued!\n");
    break;

  case 2:
    file_COMPILE(&argc, 0, argv[1]);
    DIS_END_TIME(&begin, &end);
    break;

  case 3:
    file_COMPILE(&argc, argv[2], argv[1]);
    DIS_END_TIME(&begin, &end);
    printf("____________________________\n");

    char in_f[5] = "in", op_f[5] = "op";
    in_f[2] = *(argv[2]);
    op_f[2] = *(argv[2]);
    !fopen(in_f, "r") ? fprintf(stderr, "Input file %s missing! \n", in_f), exit(EXIT_FAILURE) : 0;
    !fopen(op_f, "r") ? fprintf(stderr, "Expected output file %s missing! \n", op_f), exit(EXIT_FAILURE) : 0;

    UPDATE_OUTP(argv[1], &in_f[0], "output");
    //printf("file size: %d\n", (int)GET_SIZE("output"));
    //exit(0);
    //(int)(GET_SIZE("output")) ? fprintf(stderr, "output file is empty!\n"), exit(EXIT_FAILURE): 0;
    __TRIM__(&in_f[0]);
    __TRIM__(&op_f[0]);


    DISPLAY_EXPECTED_OUTPUT("output", &op_f[0]);
    __CMP__(&op_f[0], "output");
    break;
  }

  return 0;
}
