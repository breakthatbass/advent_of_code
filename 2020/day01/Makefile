CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
SRC=main.c
LIBS=

all: $(SRC)
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -fsanitize=address -g

time: $(SRC)
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -O3 -Os
	hyperfine --warmup 10 --min-runs 30 './a.out < input'
	rm a.out

clean:
	rm a.out
