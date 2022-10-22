package main

import (
	"strconv"
	"os"
	"fmt"
	"bufio"
	"strings"
	"time"
	"math/rand"
)

const INPUT = "input"

const CHECK = 19690720

func main() {

	fmt.Println("part 1:", part1())
	fmt.Println("part 2:", part2())
}

func part1() int {
	n, _ := loadIntoMemory(INPUT)
	// restore 1202 program alarm
	n[1] = 12
	n[2] = 2
	return intcode(n, false)
}


func part2() int {
	var noun int
	var verb int
	array, _ := loadIntoMemory(INPUT)
	arrSize := len(array)

	rand.Seed(time.Now().Unix())

	for true {
		// probably not the most efficient way to handle finding
		// the noun and verb as it test with values that have already
		// shown to be wrong. i'm not sure that starting at 0 and going
		// to 99 on the noun and then the verb would be any more efficient.
		// the best way would probably to use random numbers but
		// save the values alreayd proven to be wrong and check
		// against those...TODO later
		// interestingly, using random numbers causes a large range
		// in the amount of time this takes
		// ranges from ~5 ms to ~18 ms
		noun = rand.Intn(99)
		verb = rand.Intn(99)

		// allocate space and make a copy of the original array
		ints := make([]int, arrSize)
		n := copy(ints, array)
		if n != arrSize {
			fmt.Println("not all copied")
		}
		
		ints[1] = noun
		ints[2] = verb
		ret := intcode(ints, false)
		if ret == CHECK {
			return 100*noun + verb
			break
		}
	}
	return -1
}



func intcode(program []int, DEBUG bool) int {
	const (
		ADD   = 1 // adds the two parameters
		MULT  = 2 // multiplies the two parameters
		STORE = 3 // takes input, stores that at address[parameter]
		OUT   = 4 // outputs value at address[paramter]
		STOP  = 99
	)

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
func loadIntoMemory(file string) ([]int, error) {
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
