CC=gcc
CFLAGS=-g -Wall -Werror -W -Wextra -pedantic -O2
SRC_FILE=main.c lib/baglist.c

NAME=bags

all: $(NAME)

$(NAME): $(SRC_FILE)
	$(CC) $(SRC_FILE) -o $(NAME) $(CFLAGS)

clean:
	rm -rf *dSYM $(NAME)
