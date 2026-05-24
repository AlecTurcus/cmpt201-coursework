#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Please enter some text: ");
  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char = getline(&buff, &size, stdin);
  if (num_char == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }
  char *saveptr;
  char *out = strtok_r(buff, " ", &saveptr);
  printf("Tokens: ");
  while (out) {
    printf("\n\t%s", out);
    out = strtok_r(NULL, " ", &saveptr);
  }
  free(buff);
  return 0;
}
