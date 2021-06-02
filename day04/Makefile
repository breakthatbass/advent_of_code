CC=gcc
CFLAGS=-O2 -Wall -Wextra -pedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing

all: a.out

a.out: main.c ../lib/strlib.c ../lib/split.c
	$(CC) main.c ../lib/strlib.c ../lib/split.c $(CFLAGS)