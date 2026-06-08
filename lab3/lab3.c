#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void output(char *arr[]) {
  while (1) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
      printf("Enter input: ");
      char *buff = NULL;
      size_t size = 0;
      ssize_t num_char = getline(&buff, &size, stdin);
      arr[i] = buff;
      count++;
      if (strcmp(buff, "print\n") == 0) {
        break;
      }
    }
    for (int i = 0; i < count; i++) {
      printf("%s", arr[i]);
      free(arr[i]);
    }
  }
}

int main() {
  char *a[5];
  output(a);
  return 0;
}
