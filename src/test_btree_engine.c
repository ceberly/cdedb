#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree_engine.h"

int main(void) {
  struct Engine engine = new_btree_engine();

  printf("testing...\n");
  return EXIT_SUCCESS;
}
