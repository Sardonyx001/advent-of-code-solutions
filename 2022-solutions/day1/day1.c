#include <assert.h>
#include <bits/stdc++.h>
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

  int max1 = 0;
  int max2 = 0;
  int max3 = 0;
  int cumsum = 0;

  char *line = NULL;
  size_t len = 0;
  const char *filename = argv[1];
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    perror("Unable to open file!");
  }

  while (getline(&line, &len, input) != -1) {
    int cals = atoi(line);
    cumsum += cals;
    if (cals == 0) {
      if (cumsum > max3) {
        int tmp_max3 = max3;
        int tmp_max2 = max2;
        max3 = cumsum;
        max2 = tmp_max3;
        max1 = tmp_max2;
      } else if (cumsum > max2) {
        int tmp_max2 = max2;
        max2 = cumsum;
        max1 = tmp_max2;
      } else if (cumsum > max1) {
        max1 = cumsum;
      }
      cumsum = 0;
    }
  }

  printf("answer = %d\n", max1 + max2 + max3);
  fclose(input);
  free(line);
  return 0;
}
