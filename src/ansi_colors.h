#include <stdio.h>

void COLOR_green() {
  printf("\033[1;32m\n");
}
void COLOR_red() {
  printf("\033[1;31m\n");
}
void _RESET () { printf("\033[0m"); }

void EXIT_CODE_ONE() {
  printf("EXIT_CODE_1\n");
}

void EXIT_CODE_ZERO() {
  printf("EXIT_CODE_0\n");
}

void _PASSED () {
  printf("Passed!\n\n");
  printf("1 / 1 tests Passed!\n");
}

void _FAILED () {
  printf("Failed!\n\n");
  printf("0 / 1 tests Failed!\n");
}
