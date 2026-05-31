#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    printf("Enter a program to run.\n");
    char *buff = NULL;
    size_t size = 0;
    ssize_t num_char = getline(&buff, &size, stdin);
    buff[num_char - 1] = '\0';

    char path[num_char];
    for (int i = 0; i < num_char; i++) {
      path[i] = buff[i];
    }

    char *saveptr;
    char *out = strtok_r(buff, "/", &saveptr);
    char *arg;
    while (out) {
      arg = out;
      out = strtok_r(NULL, "/", &saveptr);
    }

    pid_t child = fork();
    if (child == 0) {
      execl(path, arg, NULL);
      printf("Exec failure\n");
    } else {
      waitpid(child, 0, 0);
    }
    free(buff);
  }
  return 0;
}
