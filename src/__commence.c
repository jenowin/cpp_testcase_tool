#include "file_manipulate.c"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

void file_SLIPED(const char* _f) {
  fprintf(stderr, "Can't open %s\n", _f), exit(EXIT_FAILURE);
  return;
}

void HAND_ARG(const int* ARG_cnt, const char* fname, const char* inputfile, const char* tempfile, FILE** const SRC_F, FILE** const TEMP_F) {

  switch(*ARG_cnt) {

    case 1:
      fprintf(stderr, "No file Arguments! \n"), exit(EXIT_FAILURE);
      break;
    case 2 ... 3:
      fopen_s(&(*SRC_F), inputfile, "r") != 0 ? file_SLIPED(fname): 0;
      fopen_s(&(*TEMP_F), tempfile, "w") != 0 ? fprintf(stderr, "Can't create tempfile %s\n", tempfile), exit(EXIT_FAILURE): 0;
      fclose(*SRC_F);
      fclose(*TEMP_F);
      break;
  }
  return;
}

void CHECK_POSSIBLITY(long** const LINE_POS, char** const MEM_BUFF) {
  LINE_POS == NULL || MEM_BUFF == NULL ? fprintf(stderr, "Can't allocate memory\n"), exit(EXIT_FAILURE) : 0;
  return;
}

void __TRIM__(const int* argc, const char* fname, const char* inputfile) {

  char tempfile[15] = "TEMP_FILE.tmp";

  FILE *src_FILE, *temp_FILE;

  HAND_ARG(argc, &fname[0], &inputfile[0], &tempfile[0], &src_FILE, &temp_FILE);

  fopen_s(&src_FILE, inputfile, "r");
  fopen_s(&temp_FILE, tempfile, "w");

  int CH = 0, TOT_LINES = 0, LEN = 0, MAX_alloc = 0;
  int FIRST_SPACE_HIT_POS = 0, hit_flag = 0;
  char prev_CH; int i = 0;
  while((CH = fgetc(src_FILE)) != EOF) {
    LEN++;
    if(CH == ' '){
      if(!hit_flag) {
        FIRST_SPACE_HIT_POS = LEN;
        hit_flag = 1;
      }
    } else {
      hit_flag = 0;
    }

    if(prev_CH != ' ' && CH == '\n') {
      FIRST_SPACE_HIT_POS = LEN;
    }

    if(CH == '\n') {
      TOT_LINES++;
      BEGIN_RIGHT_SPACE[i] = FIRST_SPACE_HIT_POS - 1;
      MAX_alloc = MAX(MAX_alloc, LEN);
      LEN = 0;
      hit_flag = 0;
      i++;
    }
    prev_CH = CH;
  }

  long *LINE_POS = malloc((TOT_LINES + 1) * sizeof *LINE_POS);
  char *MEM_BUFF = malloc(MAX_alloc + 1);

  CHECK_POSSIBLITY(&LINE_POS, &MEM_BUFF);

  int it = 0; LINE_POS[it]  = 0;

  rewind(src_FILE);
  while((CH = fgetc(src_FILE)) != EOF)
    if(CH == '\n'){ LINE_POS[++it] = ftell(src_FILE); }

  int CHAR_HIT_BOTTOM = 0;
  rewind(src_FILE);
  for(int i = TOT_LINES - 1; i >= 0; --i) {

    fseek(src_FILE, LINE_POS[i], SEEK_SET);
    fgets(MEM_BUFF, MAX_alloc + 1, src_FILE);

    if(!is_EMPTY_LINE(MEM_BUFF)) {
      CHAR_HIT_BOTTOM = i+1;
      break;
    }
  }

  rewind(src_FILE);
  WRITE_FILE(&src_FILE, &temp_FILE, &CHAR_HIT_BOTTOM, &MEM_BUFF);

  remove(inputfile);
  rename(tempfile, inputfile);


  fclose(src_FILE);
  fclose(temp_FILE);
  free(MEM_BUFF);
  free(LINE_POS);

  return;
}
