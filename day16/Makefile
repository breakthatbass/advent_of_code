CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -pedantic -Wuninitialized -fsanitize=address

all : main.c
	$(CC) main.c -o tkt $(CFLAGS)

clean:
	rm tkt
