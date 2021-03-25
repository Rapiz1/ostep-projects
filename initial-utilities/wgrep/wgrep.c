#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buf;
int buf_len;

void search(FILE *f, const char *keyword) {
  int line_len = 0, len = 0;
  int keyword_len = strlen(keyword);
  while (1) {
    line_len = 0;
    do {
      char *ret = fgets(buf + line_len, buf_len - line_len, f);
      if (!ret) {
        len = 0;
        break;
      }
      len = strlen(buf + line_len);
      line_len += len;
      if (buf_len == line_len) {
        buf_len *= 2;
        buf = realloc(buf, buf_len);
      }
    } while (len && buf[line_len - 1] != '\n');
    bool line_ok = false;
    for (int i = 0; i + keyword_len <= line_len; i++) {
      bool ok = !strncmp(buf + i, keyword, keyword_len);
      if (ok) {
        line_ok = true;
        break;
      }
    }
    if (line_ok) printf("%s", buf);
    // if (line_ok) printf("find %s with line len %d\n", keyword, line_len);
    if (!len) break;
  }
}

int main(int argc, char **argv) {
  buf = malloc(BUFSIZ);
  buf_len = BUFSIZ;
  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }

  if (argc == 2)
    search(stdin, argv[1]);
  else
    for (int i = 2; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");
      if (!f) {
        printf("wgrep: cannot open file\n");
        return 1;
      }
      search(f, argv[1]);
      fclose(f);
    }
  free(buf);
}
