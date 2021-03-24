#include <stdio.h>
#include <stdlib.h>

char buf[BUFSIZ];
int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stdout, "wcat: cannot open file\n");
      exit(1);
    }
    int n;
    do {
      n = fread(buf, 1, BUFSIZ, f);
      fwrite(buf, 1, n, stdout);
    } while (n);
    fclose(f);
  }
}
