package main

import (
	"bufio"
	"os"
	"strconv"
)

/**
 * ReadInts
 *
 * @desc: read in lines from stdin and convert to ints
 *
 * @return: array of ints
 *
 * this functions expects actual ints coming in
 * as is a typical puzzle input in AoC
 *
 * @usage: ./exe < input-file
 **/
func ReadInts() []int {
	var n []int
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		line, _ := strconv.Atoi(scan.Text())
		n = append(n, line)
	}
	return n
}
