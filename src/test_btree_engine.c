#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "btree_engine.h"

int main(void) {
  srand((unsigned int)time(NULL));

  struct Engine *engine = new_btree_engine("test/btree.db");

  struct {
    u32 key;
    i64 value;
  } oracle[1000];

  for (int i = 0; i < 1000; i++) {
    u32 key = rand() % 100000;
    i64 value = rand() % 100000;

    oracle[i].key = key;
    oracle[i].value = value;

    assert(engine->insert(key, value) == 0);
  }

  for (int i = 0; i < 1000; i++) {
    u32 key = oracle[i].key;
    i64 value;

    assert(engine->get(key, &value) == 0);
    assert(value == oracle[i].value);
  }

  btree_engine_destroy(engine);

  return EXIT_SUCCESS;
}
