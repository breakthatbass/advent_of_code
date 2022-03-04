/***
 * Intcode compiler - version 1
 *
 * 1 - ADD
 * 2 - MULT
 * 99 - QUIT
 *
 * */

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

/** convert an array of string ints to int ints **/
func atoiArray(s []string) []int {
	var a []int

	for _, i := range s {
		n, _ := strconv.Atoi(i)
		a = append(a, n)
	}
	return a
}

/**
 * read in a list of intcode numbers
 **/
func readToString() []string {
	var buf string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		buf = scanner.Text()
	}

	intcodes := strings.Split(buf, ",")
	return intcodes
}

func interpreter(intcode []int) int {

	//l := len(intcode)

	// restore 1202 program alarm
	intcode[1] = 12
	intcode[2] = 2

	fmt.Println(intcode)

	for i := 0; i < len(intcode); i += 4 {
		opcode := intcode[i]
		input1 := intcode[i+1]
		input2 := intcode[i+2]
		output := intcode[i+3]

		fmt.Printf("OP: %d, IN1: %d, IN2: %d, OUT: %d\n", opcode, input1, input2, opcode)

		switch opcode {
		case 1:
			// ADD
			intcode[output] = intcode[input1] + intcode[input2]
			break
		case 2:
			// MULTIPLY
			intcode[output] = intcode[input1] * intcode[input2]
			break
		case 99:
			// HALT
			fmt.Println("\n\n")
			fmt.Println(intcode)
			return intcode[0]
			break
		default:
			fmt.Printf("error: %d: unknown opcode\n", opcode)
			break
		}
	}
	return -1
}

func main() {

	// read in list of ints
	c := readToString()

	// convert strings to an array of ints
	intcodes := atoiArray(c)
	n := interpreter(intcodes)
	fmt.Println(n)
}
