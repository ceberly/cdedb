CFLAGS=-O2 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -std=c11 \
			 -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion
CFLAGS_SAN=-fsanitize=undefined -fsanitize=address -fsanitize-trap

BTREE_ENGINE_C=src/btree_engine.c src/engine.c
BTREE_ENGINE_H=src/engine.h src/btree_engine.h

test: ${BTREE_ENGINE_C} ${BTREE_ENGINE_H} src/test_btree_engine.c
	clang ${CFLAGS} ${CFLAGS_SAN} ${BTREE_ENGINE_C} src/test_btree_engine.c -o \
		build/test_btree_engine && ./build/test_btree_engine

format:
	clang-format -i ${BTREE_ENGINE_C} ${BTREE_ENGINE_H}
