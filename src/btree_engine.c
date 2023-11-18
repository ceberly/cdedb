#include "btree_engine.h"

#include <assert.h>
#include <stdio.h>

#include <stdlib.h>
static_assert(NULL == 0, "get a better computer.");

#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE 1024 // bytes = 1kb
#define MAGIC "CDEB"

struct btree_state {
  int openfd;
};

static u8 insert(u32 key, i64 value) { return 0; }

static u8 get(u32 key, i64 *value) { return 0; }

static int log_and_fail(const char *msg) {
  fprintf(stderr, "%s\n", msg);
  return -1;
}

int possibly_init_file(int fd) {
  off_t size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    return log_and_fail(strerror((int)size));
  }

  if (size < PAGE_SIZE) {
    u8 first_page[PAGE_SIZE] = {0};
    memcpy(first_page, MAGIC, 4);

    ssize_t n = write(fd, first_page, PAGE_SIZE);
    if (n < 0) {
      return log_and_fail(strerror((int)n));
    }

    if (n < PAGE_SIZE) {
      return log_and_fail("header writing failed");
    }

    return 0;
  }

  if (size % PAGE_SIZE != 0) {
    return log_and_fail("database is probably corrupt!");
  }

  if (lseek(fd, 0, SEEK_SET)) {
    perror("lseek");
    return -1;
  }

  u8 b[4];
  ssize_t n = read(fd, b, 4);
  if (n < 0) {
    return log_and_fail(strerror((int)n));
  }

  if (memcmp(b, MAGIC, 4) != 0) {
    return log_and_fail("magic number is wrong, probably corrupt!");
  }

  return 0;
}

struct Engine *new_btree_engine(const char *backing_file) {
  int fd = open(backing_file, O_RDWR | O_CREAT, 0666);
  if (fd < 0) {
    perror(backing_file);
    return 0;
  }

  if (possibly_init_file(fd) < 0) {
    close(fd);
    return 0;
  }

  struct Engine *e = malloc(sizeof(struct Engine));
  assert(e != 0);

  struct btree_state *state = malloc(sizeof(struct btree_state));
  assert(state != 0);

  state->openfd = fd;

  e->insert = insert;
  e->get = get;
  e->state = (void *)state;

  return e;
}

void btree_engine_destroy(struct Engine *engine) {
  if (engine != 0) {
    if (engine->state != 0) {
      close(((struct btree_state *)engine->state)->openfd);
      free(engine->state);
    }

    free(engine);
  }
}
