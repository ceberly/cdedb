#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 64

char Store[PAGE_SIZE * 10];

void insert(char *store, int key, int value) { return; }

void get(char *store, int key, int *value) { *value = 2; }

int main(void) {
  insert(Store, 1, 100);
  insert(Store, 2, 200);
  insert(Store, 3, 300);

  int one, two, three;
  get(Store, 1, &one);
  get(Store, 2, &two);
  get(Store, 3, &three);

  printf("%d %d %d\n", one, two, three);

  return EXIT_SUCCESS;
}
