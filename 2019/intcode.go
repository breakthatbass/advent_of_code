package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// instructions
const (
	ADD   = 1 // adds the two parameters
	MULT  = 2 // multiplies the two parameters
	STORE = 3 // takes input, stores that at address[parameter]
	OUT   = 4 // outputs value at address[paramter]
	STOP  = 99
)

func RunIntcode(program []int, DEBUG bool) int {

	for i := 0; i < len(program); i += 4 {
		opcode := program[i]
		input1 := program[i+1]
		input2 := program[i+2]
		output := program[i+3]

		if DEBUG {
			fmt.Printf("OP: %d, IN1: %d, IN2: %d, OUT: %d\n", opcode, input1, input2, opcode)
		}

		switch opcode {
		case ADD:
			program[output] = program[input1] + program[input2]
			break
		case MULT:
			program[output] = program[input1] * program[input2]
			break
		case STOP:
			if DEBUG {
				fmt.Println()
				fmt.Println(program)
			}
			return program[0]
		default:
			fmt.Printf("error: %d: unknown opcode\n", opcode)
			break
		}
	}
	return -1
}

//================================================//
// utilities for intcode programs				  //
//================================================//

// convert an array of string ints to int ints
func atoiArray(s []string) []int {
	var a []int

	for _, i := range s {
		n, _ := strconv.Atoi(i)
		a = append(a, n)
	}
	return a
}

// read the file and load the program into memory
func LoadIntoMemory(file string) ([]int, error) {
	fp, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	defer fp.Close()

	scanner := bufio.NewScanner(fp)
	scanner.Scan()
	buf := scanner.Text()
	fp.Close()

	s := strings.Split(buf, ",")
	return atoiArray(s), nil
}
