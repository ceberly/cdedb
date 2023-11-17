#include "btree_engine.h"

#include <assert.h>
#include <stdlib.h>

static u8 insert(u32 key, i64 value) {
  return 0;
}

static u8 get(u32 key, i64 *value) {
  return 0;
}

struct Engine *new_btree_engine(const char *backing_file) {
  struct Engine *e = malloc(sizeof (struct Engine));
  assert(e != NULL);

  e->insert = insert;
  e->get = get;
  e->state = NULL;

  return e;
}

void btree_engine_destroy(struct Engine *engine) {
  if (engine != NULL) {
    if (engine->state != NULL) {
      free(engine->state);
    }

    free(engine);
  }
}
