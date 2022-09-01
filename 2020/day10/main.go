/**
 * day 10 2020
 * https://adventofcode.com/2020/day/10
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"fmt"
	"bufio"
	"strings"
	"os"
	"sort"
)

func jolts(adapters []int) int {
	ones := 0
	threes := 0
	joltDiff := 0
	prevAdapter := 0 // start with wall

	for i := 0; i < len(adapters); i++ {
		joltDiff = adapters[i] -  prevAdapter
		if joltDiff == 1 {
			ones++
		} else if joltDiff == 3 {
			threes++
		}
		prevAdapter = adapters[i]
	}
	// jolt difference from device
	threes++

	return ones*threes
}

func main() {
	var adapters []int
	var n int

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		f := strings.NewReader(scan.Text())
		fmt.Fscanf(f, "%d", &n)
		adapters = append(adapters, n)
	}
	sort.Ints(adapters[:])

	fmt.Println("Part 1:", jolts(adapters))
}