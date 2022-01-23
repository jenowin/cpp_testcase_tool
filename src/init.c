#include<sys/time.h>
#include<string.h>
#include "ansi_colors.h"
#include "__commence.c"
#include "memory_calc.h"

char CC[2] = "14";
void file_COMPILE(const int* ARG_cnt, const char* test, const char* fname){
  char commands[380];
  sprintf(commands, "g++ -std=c++%s -O2 -g -Wall -Wshadow \"-Wl,--stack=268435456\" -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion  -fno-sanitize-recover=all -fstack-protector-all -D FORTIFY_SOURCE=2  -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -o %s %s.cpp", CC, fname, fname);
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

void UPDATE_OUTP(const char* fname, const char* IN, const char* OP) {
  char cmd[20];
  sprintf(cmd, "%s<%s>%s", fname, IN, OP);
  system(cmd);
  return;
}

void DISPLAY_EXPECTED_OUTPUT(const char* in, const char* op, const char* exp_op) {
  char cmd[15];

  printf("Output:\n");
  sprintf(cmd, "type %s", op);
  system(cmd);
  printf("\n____________________________\n");

  memset(cmd, 0, sizeof cmd);

  printf("Expected:\n");
  sprintf(cmd, "type %s", exp_op);
  system(cmd);
  printf("____________________________\n");
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
    printf("No arguments argued!");
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

    UPDATE_OUTP(argv[1], &in_f[0], "output");
    __TRIM__(&argc, argv[2],  &in_f[0]);
    DISPLAY_EXPECTED_OUTPUT(&in_f[0], "output", &op_f[0]);
    __CMP__(&op_f[0], "output");
    break;
  }
  return 0;
}
