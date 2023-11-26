CFLAGS=-O2 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -std=c11 \
			 -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion
CFLAGS_SAN=-fsanitize=undefined -fsanitize=address -fsanitize-trap

.PHONY: test
test:
	clang -D TEST ${CFLAGS} ${CFLAGS_SAN} mem_btree.c -o \
		build/mem_btree && ./build/mem_btree

format:
	clang-format -i ${BTREE_ENGINE_C} ${BTREE_ENGINE_H}
