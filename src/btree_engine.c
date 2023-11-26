#include "btree_engine.h"

#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE 1024 // bytes = 1kb
#define PAGE_HEADER_LEN 12
#define MAGIC "CDEB"

#define PAGE_TABLE_ROOT 0x1
#define PAGE_TABLE_LEAF 0x2

struct btree_state {
  int openfd;
};

struct page_header {
  u8 kind;
  u8 rest[11]; // there will be 12 bytes of stuff eventually, like sqlite
};

static void page_header_as_bytes(struct page_header *p, u8 *out) {
  memset(out, 0, PAGE_HEADER_LEN);
  out[0] = p->kind;
}

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
    u8 header[PAGE_HEADER_LEN] = {0};

    struct page_header p = {.kind = PAGE_TABLE_LEAF};
    page_header_as_bytes(&p, header);

    memcpy(first_page, MAGIC, 4);
    memcpy(first_page + 4, header, PAGE_HEADER_LEN);

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
  if (e == 0) {
    return 0;
  }

  struct btree_state *state = malloc(sizeof(struct btree_state));
  if (e == 0) {
    return 0;
  }

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

// --- Tests ---

#ifdef TEST
#include <time.h>

bool oracle_test(struct Engine *engine) {
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
      return false;
    }
  }

  for (int i = 0; i < 1000; i++) {
    u32 key = oracle[i].key;
    i64 value;

    if (engine->get(key, &value) != 0) {
      fprintf(stderr, "oracle(): failed to get\n");
      return false;
    }

    if (value != oracle[i].value) {
      fprintf(stderr, "oracle(): expected %zu got %zu instead.\n",
              oracle[i].value, value);
      return false;
    }
  }

  return true;
}

int main(void) {
  srand((unsigned int)time(NULL));

  struct Engine *engine = new_btree_engine("test/btree.db");
  if (engine == NULL) {
    return EXIT_FAILURE;
  }

  if (!oracle_test(engine)) {
    goto fail;
  }

  btree_engine_destroy(engine);
  return EXIT_SUCCESS;

fail:
  btree_engine_destroy(engine);
  return EXIT_FAILURE;
}

#endif
