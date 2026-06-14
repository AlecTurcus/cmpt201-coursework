#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void *increase_heap(int size) {
  void *addr = sbrk(size);
  return addr;
}

void initialize_block(struct header *block, int val) {
  memset((void *)block + sizeof(struct header), val, 112);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[128];
  ssize_t len = snprintf(buf, 128, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprintf failed");
    return;
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  struct header *first_block = (struct header *)increase_heap(256);
  first_block->size = 128;
  first_block->next = NULL;
  initialize_block(first_block, 0);

  struct header *second_block = (struct header *)((void *)first_block + 128);
  second_block->size = 128;
  second_block->next = first_block;
  initialize_block(second_block, 1);

  print_out("first block:       %p\n", &first_block, sizeof(&first_block));
  print_out("second block:      %p\n", &second_block, sizeof(&second_block));
  print_out("first block size:  %d\n", &first_block->size, sizeof(&first_block->size));
  print_out("first block next:  %p\n", &first_block->next, sizeof(&first_block->next));
  print_out("second block size: %d\n", &second_block->size, sizeof(&second_block->size));
  print_out("second block next: %p\n", &second_block->next, sizeof(&second_block->next));

  for (int i = 0; i < 112; i++) {
    uint64_t val = *((uint8_t *)first_block + sizeof(struct header) + i);
    print_out("%d\n", &val, sizeof(&second_block->size));
  }

  for (int i = 0; i < 112; i++) {
    uint64_t val = *((uint8_t *)second_block + sizeof(struct header) + i);
    print_out("%d\n", &val, sizeof(&second_block->size));
  }
  return 0;
}
