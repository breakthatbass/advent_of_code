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

const DEBUG = true

// convert an array of string ints to int ints
func atoiArray(s []string) []int {
	var a []int

	for _, i := range s {
		n, _ := strconv.Atoi(i)
		a = append(a, n)
	}
	return a
}

// read in a list of intcode numbers
func readToString() []string {
	var buf string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		buf = scanner.Text()
	}

	intcodes := strings.Split(buf, ",")
	return intcodes
}

func main() {

	// read in list of ints
	c := readToString()

	// convert strings to an array of ints
	intcodes := atoiArray(c)
	n := Interpreter(intcodes, DEBUG)
	fmt.Println(n)
}
