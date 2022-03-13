package main

import (
	"fmt"
)

const LEN = 2000 // 2000 lines in input file

func part1(n []int) int {
	increase := 0
	prev := n[0]
	for i := 1; i < LEN; i++ {
		if n[i] > prev {
			increase++
		}
		prev = n[i]
	}
	return increase
}

func part2(n []int) int {
	increase := 0
	prev := n[0] + n[1] + n[2]
	for i := 1; i < LEN; i++ {

		if i+1 >= LEN || i+2 >= LEN {
			break
		}
		cur := n[i] + n[i+1] + n[i+2]
		if cur > prev {
			increase++
		}
		prev = cur
	}
	return increase
}

func main() {
	n := ReadInts()

	fmt.Println(part1(n))
	fmt.Println(part2(n))
}
