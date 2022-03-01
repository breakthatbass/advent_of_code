package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"time"
)

var a int
var b int

func readInts() []int {
	var n []int
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		line, _ := strconv.Atoi(scan.Text())
		n = append(n, line)
	}
	return n
}

func part1(n []int) {
	for i, i2 := range n {
		time.Sleep(1 * time.Second)
		for j, j2 := range n {
			if i == j {
				continue
			}
			if i2+j2 == 2020 {
				a = i2 * j2
				return
			}
		}
	}
	return
}

func part2(n []int) {
	for i, i2 := range n {
		time.Sleep(1 * time.Second)
		for j, j2 := range n {
			for k, k2 := range n {
				if i == j && i == k {
					continue
				}
				if i2+j2+k2 == 2020 {
					b = i2 * j2 * k2
					return
				}
			}
		}
	}
	return
}

func main() {

	nums := readInts()
	a = 0
	b = 0

	go part1(nums)
	go part2(nums)

	fmt.Println(a, b)
}
