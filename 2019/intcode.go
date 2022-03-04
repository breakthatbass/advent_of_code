package main

import "fmt"

// run the intcode virtual machine
func Interpreter(intcode []int, DEBUG bool) int {

	// restore 1202 program alarm
	intcode[1] = 12
	intcode[2] = 2

	if DEBUG {
		fmt.Println(intcode)
		fmt.Println("\nIntCode Program:\n")
	}

	for i := 0; i < len(intcode); i += 4 {
		opcode := intcode[i]
		input1 := intcode[i+1]
		input2 := intcode[i+2]
		output := intcode[i+3]

		if DEBUG {
			fmt.Printf("OP: %d, IN1: %d, IN2: %d, OUT: %d\n", opcode, input1, input2, opcode)
		}

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
			if DEBUG {
				fmt.Println()
				fmt.Println(intcode)
			}
			return intcode[0]
		default:
			fmt.Printf("error: %d: unknown opcode\n", opcode)
			break
		}
	}
	return -1
}
