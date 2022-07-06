/**
 * day 03 2020
 * https://adventofcode.com/2020/day/3
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
)

var hill []string	// the grid...or ski hill
var hillLen int

/*	ride the toboggan down the hill and hit some trees!
 *	...and count them while you're at it. */
 func rideSnowyHill(right int, down int) int {
	x := 0
	y := 0
	treeCount := 0

	for x < hillLen {
		// the width of the grid is 31 so having 'y % 31' brings you
		// to the opposite side if you go past the end
		if (hill[x][y % 31] == '#') {
			treeCount++
		}
		y += right
		x += down
	}
	return treeCount
 }

func main() {
	
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		hill = append(hill, scan.Text())
	}

	hillLen = len(hill)

	p1 := rideSnowyHill(3, 1)

	// part 2
	slopes := 1
	slopes *= rideSnowyHill(1, 1);
	slopes *= rideSnowyHill(3, 1);
	slopes *= rideSnowyHill(5, 1);
	slopes *= rideSnowyHill(7, 1);
	slopes *= rideSnowyHill(1, 2);

	fmt.Println("part 1:", p1)
	fmt.Println("part 2:", slopes)
}