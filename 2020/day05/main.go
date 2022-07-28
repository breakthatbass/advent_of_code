/**
 * day 05 2020
 * https://adventofcode.com/2020/day/5
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
	"sort"
)

// get upper 7 bits - the 'F' and 'B' part
func upper7Bits(b int) int {
	return (b >> 3) & 0x7F
}

// get lower 3 bits - the 'L' and 'R' part
func lower3bits(b int) int {
	return b & 0x7
}

// convert the seating chart string to an int
func toBin(s string) int {
	var n int
	for _, c := range s {
		if c == 'B' || c == 'R' {
			n = n << 1 | 1
		} else {
			n = n << 1
		}
	}
	return n
}

func findMyTicket(tkts []int) int {
	sort.Ints(tkts[:])
	// start 5 tickets in
	for i := 5; i < len(tkts); i++ {
		// the ticket we want is the missing one
		// so if tkts[i] is 713 and there is no 714
		// then 714 is our ticket
		if tkts[i + 1] != tkts[i] + 1 {
			return tkts[i] + 1
		}
	}
	return 0
}

func main() {
	largestSeat := 0
	var tkts []int // save all tkt numbers to use for part 2

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		buf := scan.Text()
		seat := toBin(buf)
		row := upper7Bits(seat)
		col := lower3bits(seat)

		// part 1 - get largest seat number
		seat = row*8 + col
		if seat > largestSeat {
			largestSeat = seat
		}
		tkts = append(tkts, seat)
	}
	// part 2
	mySeat := findMyTicket(tkts)

	fmt.Println("part 1:", largestSeat)
	fmt.Println("part 2:", mySeat)
}


