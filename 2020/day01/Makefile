CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
SRC=main.c
LIBS=

all: $(SRC)
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -fsanitize=address -g

time: $(SRC)
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -O2 -Os
	hyperfine --warmup 10 './a.out < input'

clean:
	rm a.out
