CC=gcc
CFLAGS=-O2 -Os -W -Wall -Werror -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing -fsanitize=address
SRC=main.c
LIBS=../lib/split.c ../lib/strlib.c

all: $(SRC)
	$(CC) $(SRC) $(LIBS) $(CFLAGS)
