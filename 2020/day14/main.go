/**
 * day 14 2020
 * https://adventofcode.com/2020/day/14
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"fmt"
	"strconv"
	"bufio"
	"os"
	"strings"
)

// we need two seperate masks for the logic
var maskAnd int // for the Xs we need an AND mask to keep the bits the same
var maskOr int 	// for the 1s we need an OR mask

type Mem struct {
	addr int
	val int
}
var mem []Mem


func updateBitmasks(s string) {
	maskAnd = 0
	maskOr = 0
	for _, c := range s {
		if c == 'X'{
			maskAnd = (maskAnd << 1) | 1; maskOr = (maskOr << 1) | 0
		} else if c == '1' {
			maskOr = (maskOr << 1) | 1; maskAnd = (maskAnd << 1) | 0
		} else {
			// and keep the zeros as zeros
			maskAnd = (maskAnd << 1) | 0; maskOr = (maskOr << 1) | 0
		}
	}
	//maskAnd = and
	//maskOr = or
}


// get the memory location and the value to write
func getMemInfo(s string) (int, int) {
	var memLoc int
	line := strings.Split(s, " ")
	// now line[0] is mem[xxxxxx]
	// and line[2] is the value to write
	fmt.Sscanf(line[0], "mem[%d]", &memLoc)
	memVal, _ := strconv.Atoi(line[2]) // dont worry about nil, it'll always be an int
	return memLoc, memVal
}


// have we already written to this address? if yes, return index in array
func checkMemLocation(addr int) int {
	for i, m := range mem {
		if m.addr == addr {
			return i
		}
	}
	return -1
}


func addUpMemoryValues() int {
	t := 0
	for _, m := range mem {
		t += m.val
	}
	return t
}


func main() {
	scan := bufio.NewScanner(os.Stdin)

	for scan.Scan() {
		buf := scan.Text()
		if buf[0] == 'm' && buf[1] == 'a' {
			// mask - grab just the binary string
			mask := buf[7:]
			updateBitmasks(mask)
		} else {
			// else we have a memory location
			memLocation, memValue := getMemInfo(buf)

			// apply the masks
			memValue = (memValue & maskAnd) | maskOr

			// have we already written to this memory address?
			found := checkMemLocation(memLocation)
			if found == -1 {
				m := Mem{memLocation, memValue}
				mem = append(mem, m)
			} else {
				mem[found].val = memValue
			}
		}
	}
	part1 := addUpMemoryValues()
	fmt.Println("part 1:", part1)
}