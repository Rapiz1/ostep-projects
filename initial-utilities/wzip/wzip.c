#include <stdio.h>
#include <stdlib.h>

char **files_list;
int files_count;
FILE *cur_file;
int cur_file_pos;
int files_getc() {
  if (!cur_file) {
    cur_file = fopen(files_list[cur_file_pos++], "rb");
    if (!cur_file) {
      fputs("wzip: cannot open file", stderr);
      exit(1);
    }
  }
  int ret = fgetc(cur_file);
  if (ret == EOF) {
    if (cur_file_pos == files_count) return EOF;

    fclose(cur_file);
    cur_file = NULL;
    ret = files_getc();
  }
  return ret;
}

void zip() {
  char ch = files_getc(), pre_ch = ch;
  if (ch == EOF) return;
  while (1) {
    u_int32_t len = 0;
    do {
      ch = files_getc();
      len++;
    } while (ch != EOF && ch == pre_ch);
    fwrite(&len, sizeof(len), 1, stdout);
    fputc(pre_ch, stdout);
    if (ch == EOF) break;
    pre_ch = ch;
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    puts("wzip: file1 [file2 ...]");
    return 1;
  }
  files_list = argv + 1;
  files_count = argc - 1;
  zip();
}
