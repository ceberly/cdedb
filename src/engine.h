#ifndef ENGINE_H
#define ENGINE_H

#include "useful_defs.h"

struct Engine {
  u8 last_error;
  void *state; // awesome.

  u8 (*insert)(u32 key, i64 value);
  u8 (*get)(u32 key, i64 *value);
};

void engine_print_error(u8 err);

#endif
