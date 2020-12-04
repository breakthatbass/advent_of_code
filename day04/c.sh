#usr/bin/bash

BIN=passport

if test -f "$BIN"; then
    make clean && make
else
    make
fi
