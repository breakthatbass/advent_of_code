#!/bin/bash

# usage: ./bake.sh <day>
# example: ./bake.sh day01

# we like options...fsanatize slows it down a bit but it keeps our memory issues away
CFLAGS='-O2 -Os -Wall -Wextra -pedantic -Wshadow -Werror -Wstrict-overflow -fno-strict-aliasing -fsanitize=address'

# compile
gcc "$1"/main.c $CFLAGS

# run program
./a.out < "$1"/input

# clean up
rm a.out