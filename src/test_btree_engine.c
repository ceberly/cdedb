#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "btree_engine.h"

int main(void) {
  srand((unsigned int)time(NULL));

  struct Engine *engine = new_btree_engine("test/btree.db");
  if (engine == NULL) {
    return EXIT_FAILURE;
  }

  struct {
    u32 key;
    i64 value;
  } oracle[1000];

  for (int i = 0; i < 1000; i++) {
    u32 key = rand() % 100000;
    i64 value = rand() % 100000;

    oracle[i].key = key;
    oracle[i].value = value;

    if (engine->insert(key, value) != 0) {
      fprintf(stderr, "failed to insert\n");
      goto fail;
    }
  }

  for (int i = 0; i < 1000; i++) {
    u32 key = oracle[i].key;
    i64 value;

    if (engine->get(key, &value) != 0) {
      fprintf(stderr, "failed to get\n");
      goto fail;
    }
    
    if (value != oracle[i].value) {
      fprintf(stderr, "expected %zu got %zu instead.\n", oracle[i].value, value);
      goto fail;
    }
  }

  btree_engine_destroy(engine);
  return EXIT_SUCCESS;

fail:
  btree_engine_destroy(engine);
  return EXIT_FAILURE;
}
