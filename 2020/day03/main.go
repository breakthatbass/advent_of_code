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
 func rideSnowyHill(right int, down int) int64 {
	x := 0
	y := 0
	var treeCount int64 = 0

	for x < hillLen {
		// the width of the grid is 31 so have 'y % 31' will bring you
		// to the opposite side if you go past the end in the same way
		// you do in super mario bros 2
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
	var slopes int64 = 1
	slopes *= rideSnowyHill(1, 1);
	slopes *= rideSnowyHill(3, 1);
	slopes *= rideSnowyHill(5, 1);
	slopes *= rideSnowyHill(7, 1);
	slopes *= rideSnowyHill(1, 2);

	fmt.Println("part 1:", p1)
	fmt.Println("part 2:", slopes)
}