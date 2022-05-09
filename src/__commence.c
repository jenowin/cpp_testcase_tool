#include "file_manipulate.c"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

void CHECK_POSSIBLITY(long** const LINE_POS, char** const MEM_BUFF) {
  LINE_POS == NULL || MEM_BUFF == NULL ? fprintf(stderr, "Can't allocate memory\n"), exit(EXIT_FAILURE) : 0;
}

void __TRIM__(const char* inputfile) {

  char tempfile[15] = "TEMP_FILE.tmp";

  FILE *src_FILE = fopen(inputfile, "r");
  FILE *temp_FILE = fopen(tempfile, "w");

  !temp_FILE ? fprintf(stderr, "Can't create tempfile %s\n", tempfile), exit(EXIT_FAILURE): 0;


  int TOT_LINES = 0, LEN = 0, LINE_LEN = 0;
  int FIRST_SPACE_HIT_POS = 0, hit_flag = 0;
  char CH, prev_CH; int i = 0;
  while((CH = (char)fgetc(src_FILE)) != EOF) {
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
      LINE_LEN = MAX(LINE_LEN, LEN);
      LEN = 0;
      hit_flag = 0;
      i++;
    }
    prev_CH = CH;
  }

  long *LINE_POS = malloc((TOT_LINES + 1) * sizeof *LINE_POS);
  char *MEM_BUFF = malloc(LINE_LEN + 1);

  CHECK_POSSIBLITY(&LINE_POS, &MEM_BUFF);

  int it = 0; LINE_POS[it]  = 0;

  rewind(src_FILE);
  while((CH = (char)fgetc(src_FILE)) != EOF)
    if(CH == '\n'){ LINE_POS[++it] = ftell(src_FILE); }

  int CHAR_HIT_BOTTOM = 0;
  rewind(src_FILE);
  for(i = TOT_LINES - 1; i >= 0; --i) {

    fseek(src_FILE, LINE_POS[i], SEEK_SET);
    fgets(MEM_BUFF, LINE_LEN + 1, src_FILE);

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
}
