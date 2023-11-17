#include "btree_engine.h"

static u8 insert(uint32_t key, int64_t value) {
  return 0;
}

struct Engine new_btree_engine(void) {
  struct Engine e = {
    .insert = insert,
  };

  return e;
}
