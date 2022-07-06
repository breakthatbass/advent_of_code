package main

import (
	"bufio"
	"os"
	"fmt"
	"strings"
)

func part1(n []int) int {
	for _, i := range n {
		for _, j := range n {
			if i + j == 2020 {
				return i * j
			}
		}
	}
	return -1
}

func part2(n []int) int {
	for _, i := range n {
		for _, j := range n {
			for _, k := range n {
				if i + j +k == 2020 {
					return i * j * k
				}
			}
		}
	}
	return -1
}

func main() {
	var nums []int
	var n int

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		f := strings.NewReader(scan.Text())
		fmt.Fscanf(f, "%d", &n)
		nums = append(nums, n)
	}

	a := part1(nums)
	b := part2(nums)

	fmt.Println("part 1:", a)
	fmt.Println("part 2:", b)
}
