#ifndef BTREE_ENGINE_H
#define BTREE_ENGINE_H

#include "engine.h"

struct Engine *new_btree_engine(const char *);
void btree_engine_destroy(struct Engine *);

#endif
