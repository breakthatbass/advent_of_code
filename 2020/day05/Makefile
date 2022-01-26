CC=gcc
CFLAGS=-O2 -Os -W -Wall -Werror -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing -fsanitize=address
SRC_FILES=main.c ../lib/converter.c

all: $(SRC_FILES)
	$(CC) $(SRC_FILES) $(CFLAGS)
