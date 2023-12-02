#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Comparison function. Receives two generic (void) pointers to the items under
 * comparison. */
int compare_pos(void *arr, const void *p, const void *q) {
  int x = *(const int *)p;
  int y = *(const int *)q;
  int *word_position = (int *)arr;

  return (word_position[x] > word_position[y]) -
         (word_position[x] < word_position[y]);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  char *numword[10] = {"zero", "one", "two",   "three", "four",
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
    
    printf("line = %s | length = %d\n", line, (int)linelen);
    /* boolean mask to check if i, as in words[i], exists (=1) or not (=0) */
    int *word_position = (int *)calloc(10, sizeof(int));
    /* place to store word-numbers as they appear (in order)*/
    int *num_values = (int *)calloc(linelen, sizeof(int));
    int count = 0;
    /* check if each word is present in `line` and populate `words` */
    for (int i = 0; i < 10; ++i) {
      /** get the first occurrence of the string `numword[i]` within the
       * string `line` if it exists. */
      char *sptr = strstr(line, numword[i]);
      if (sptr != NULL) {
        word_position[i] = sptr - line;
        num_values[count++] = i;
        printf("'%s' ", numword[i]);
      }
    }

    /* Sorting num_values in accordance with each element's word_position[i] */
    qsort_r(num_values, count, sizeof(int), word_position, compare_pos);

    for (int j = 0; j < count; ++j) {
      printf(" %d ", num_values[j]);
    }
    printf(" | ");

    /* iterate and find `first` and `last`digits */
    for (int i = 0; i < linelen; ++i) {
      if ((int)line[i] >= '0' && (int)line[i] <= '9') {
        int n = (int)line[i] - '0';
        printf(" %d", n);
        word_position[n] = i;
        num_values[count++] = n;
      }
    }
    printf(" | ");
    
    /* Sorting num_values in accordance with each element's word_position[i] */
    qsort_r(num_values, count, sizeof(int), word_position, compare_pos);
    for (int j = 0; j < count; ++j) {
      printf("%d", num_values[j]);
    }
    printf(" | ");

    first = num_values[0];
    last = num_values[count-1];

    printf(" |-> %d%d\n\n", first, last);
    sum += first * 10 + last;
    free(word_position);
    free(num_values);
  }

  printf("Answer = %d\n", sum);
  fclose(input);
  free(line);
  return 0;
}
