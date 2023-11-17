#ifndef ENGINE_H
#define ENGINE_H

#include "useful_defs.h"

struct Engine {
  u8 last_error;
  u8 (*insert)(u32 key, i64 value);
  void *state; // awesome.
};

void engine_print_error(u8 err);

#endif
