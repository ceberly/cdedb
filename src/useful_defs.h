#ifndef USEFUL_DEFS_H
#define USEFUL_DEFS_H

#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <stdio.h>

#include <assert.h>
#include <stdlib.h>
static_assert(NULL == 0, "get a better computer.");

typedef uint8_t u8;
typedef uint32_t u32;
typedef int64_t i64;

inline void u32_to_be(u32 in, u8 *out) {
  out[0] = (in >> 24) & 0xFF;
  out[1] = (in >> 16) & 0xFF;
  out[2] = (in >> 8) & 0xFF;
  out[3] = in & 0xFF;
}

inline void i64_to_be(i64 in, u8 *out) {
  out[0] = (in >> 56) & 0xFF;
  out[1] = (in >> 48) & 0xFF;
  out[2] = (in >> 40) & 0xFF;
  out[3] = (in >> 32) & 0xFF;
  out[4] = (in >> 24) & 0xFF;
  out[5] = (in >> 16) & 0xFF;
  out[6] = (in >> 8) & 0xFF;
  out[7] = in & 0xFF;
}

#endif
