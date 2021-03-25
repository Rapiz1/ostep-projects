#include <stdio.h>
#include <stdlib.h>

u_int8_t buf[BUFSIZ * 5];
void unzip(FILE *f) {
  int n;
  do {
    n = fread(buf, 1, BUFSIZ * 5, f);
    for (int i = 0; i < n; i += 5) {
      u_int32_t len = *(u_int32_t *)(buf + i);
      char ch = *(char *)(buf + i + 4);
      while (len--) putc(ch, stdout);
    }
  } while (n);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "rb");
    if (!f) {
      printf("wunzip: cannot open file\n");
      return 1;
    }
    unzip(f);
    fclose(f);
  }
}
