#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  char *nwords[10] = {"zero", "one", "two",   "three", "four",
                      "five", "six", "seven", "eight", "nine"};
  int sum = 0;

  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  const char *filename = argv[1];
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    perror("Unable to open file!");
  }

  while ((linelen = getline(&line, &linecap, input)) > 0) {
    int first = -1;
    int last = -1;
    printf("line = %slength = %d | ", line, (int)linelen);
    for (int i = 0; i < linelen; ++i) {
      if ((int)line[i] >= '0' && (int)line[i] <= '9') {
        printf("%d ", (int)line[i] - '0');
        if (first == -1) {
          first = last = (int)line[i] - '0';
        } else {
          last = (int)line[i] - '0';
        }
      }
    }
    printf("| %d%d\n\n", first, last);
    sum += first * 10 + last;
  }

  printf("Answer = %d\n", sum);
  fclose(input);
  free(line);
  return 0;
}
