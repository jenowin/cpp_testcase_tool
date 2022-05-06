long double GET_SIZE(const char* file) {
  FILE* fp = fopen(file, "r");

  //printf("file name : %s\n", file);
  if (fp == NULL) {
    printf("Cant find the file!\n");
    return -1;
  }

  fseek(fp, 0L, SEEK_END);

  long double res = ftell(fp);
  fclose(fp);

  return res;
}

void DISPLAY_UNITS(const long double* file_s) {

  if (*file_s >= 0 && *file_s < 1000) {
    printf("%.2Lf B \n", *file_s);
  }
  else if (*file_s >= 1000 && *file_s < 1000000) {
    printf("%.2Lf KB \n", *file_s/1024.00);
  }
  else if(*file_s >= 1000000 && *file_s < 1e+9) {
    printf("%.2Lf MB \n", *file_s/1048576.00);
  }
  else if (*file_s >= 1e+9 && *file_s < 1e+12) {
    printf("%.2Lf GB \n", *file_s/1073741824.00);
  }
  else if(*file_s >= 1e9+12) {
    printf("%.2Lf TB \n", *file_s/1099511627776.00);
  }
  return;
}

void DISPLAY_MEM_SRC_EXE(const char* file) {

  char file_ch[15];
  strcpy(file_ch, file);

#ifdef _WIN32
  strcat(file_ch, ".exe");
#endif

  printf("Memory: ");
  long double file_s = GET_SIZE(file_ch);
  DISPLAY_UNITS(&file_s);

  /*
  memset(file_ch, 0, sizeof file_ch);
  strcpy(file_ch, file);
  strcat_s(file_ch, sizeof file_ch, ".cpp");

  file_s = GET_SIZE(file_ch);
  DISPLAY_UNITS(&file_s);
  */
  return;
}
