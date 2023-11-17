#include "engine.h"

#include <assert.h>
#include <stdio.h>

void engine_print_error(u8 err) {
  switch (err) {
    case 0:
      fprintf(stderr, "None\n");
      break;
    default:
      assert(false);
  }
}
