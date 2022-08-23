/**
 * day 08 2020
 * https://adventofcode.com/2020/day/8
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"bufio"
	"os"
	"fmt"
	"strings"
)


type bootcode struct {
	instruction string
	value       int
	alreadyRun	bool
}

var gameboy []bootcode
var accumulator int
var gameboyLen int


func execBootCode(checkForEnd bool) int {
	i := 0
	for {
		if checkForEnd && i == gameboyLen {
			// on last instruction, part 2 answer
			return 1
		} else if (checkForEnd && i > gameboyLen) || gameboy[i].alreadyRun {
			// in an infinite loop
			return 0
		} else if !checkForEnd && gameboy[i].alreadyRun {
			// part 1 - exit just whenever we hit an instruction we've alreay seen
			return 0
		}

		switch gameboy[i].instruction {
		case "acc":
			gameboy[i].alreadyRun = true
			accumulator += gameboy[i].value
			i++
			break
		case "jmp":
			gameboy[i].alreadyRun = true
			i += gameboy[i].value
			break
		case "nop":
			gameboy[i].alreadyRun = true
			i++
			break
		}
	}
	return 0
}

// set all 'alreadyRun' varibles in array to false
// and set accumulator to 0
func reset() {
	for i := 0; i < gameboyLen; i++ {
		gameboy[i].alreadyRun = false
	}
	accumulator = 0
}

// set a jmp to nop or a nop to jmp
func flip(instr *string) {
	if *instr == "jmp" {
		*instr = "nop"
	} else if *instr == "nop" {
		*instr = "jmp"
	}
}


func findCorrupted() {
	for i := 0; i < gameboyLen; i++ {
		reset()
		// change instruction
		flip(&gameboy[i].instruction)
		// test it out
		if execBootCode(true) == 1 {
			break
		}
		// change it back
		flip(&gameboy[i].instruction)
	}
}


func main() {
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		f := strings.NewReader(scan.Text())
		var bc bootcode
		_, err := fmt.Fscanf(f, "%s %d", &bc.instruction, &bc.value)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Fscanf: %v\n", err)
		}
		bc.alreadyRun = false
		gameboy = append(gameboy, bc)
	}
	gameboyLen = len(gameboy)

	execBootCode(false)
	fmt.Println("part 1:", accumulator)
	findCorrupted()
	fmt.Println("part 2:", accumulator)
}
