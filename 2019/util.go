package main

import (
	"bufio"
	"os"
	"strconv"
)

func ReadInts() []int {
	var n []int
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		line, _ := strconv.Atoi(scan.Text())
		n = append(n, line)
	}
	return n
}
