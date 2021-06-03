#!/bin/bash

ARGS=$#		# the number of args. $# is cryptic and looks dumb
DAY="$1"

if [ "$ARGS" -ne 1  ]; then
	echo "error: too many arguments"
	exit 1
fi


# the nonsense below just says, "if $DAY directory does not exit..."
if [ ! -d "$DAY" ]; then
  echo "error: can't seem to find the $DAY directory"
  echo "usage: ./run.sh <day-directory>"
  exit 1
fi



# if we make it here we have a legitimate directory
echo "compiling..."
if make -C "$DAY"/; then
	echo "compiled successfully"
else
	echo "compilation failed"
	exit 1
fi

echo

./"$DAY"/a.out < "$DAY"/input
rm "$DAY"/a.out

