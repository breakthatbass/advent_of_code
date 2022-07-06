/**
 * day 02 2020
 * https://adventofcode.com/2020/day/2
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func sled(min int, max int, c byte, pass string) int {
	count := 0
	for i, _ := range pass {
		if pass[i] == c {
			count++
			i++
		}
	}
	if count >= min && count <= max {
		return 1
	}
	return 0
}

func toboggan(min int, max int, c byte, pass string) int {
	// no XOR in go but this is the same logic
	if (pass[min-1] == c) != (pass[max-1] == c) {
		return 1
	}
	return 0
}

func main() {

	var (
		min int
		max int
		c byte
		pass string
	)

	validSled := 0
	validToboggan := 0

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		f := strings.NewReader(scan.Text())

		fmt.Fscanf(f, "%d-%d %c: %s", &min, &max, &c, &pass)
		validSled += sled(min, max, c, pass)
		validToboggan += toboggan(min, max, c, pass)
	}
	fmt.Println("part 1:", validSled)
	fmt.Println("part 2:", validToboggan)
}