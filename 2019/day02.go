package main

import (
	"fmt"
	"math/rand"
	"time"
)

const FILEPATH = "inputs/2"
const CHECK = 19690720

func part1() int {
	n, _ := LoadIntoMemory(FILEPATH)
	// restore 1202 program alarm
	n[1] = 12
	n[2] = 2
	return RunIntcode(n, false)
}

func part2() int {
	var noun int
	var verb int
	rand.Seed(time.Now().Unix())
	for true {
		noun = rand.Intn(99)
		verb = rand.Intn(99)

		ints, _ := LoadIntoMemory(FILEPATH)
		ints[1] = noun
		ints[2] = verb
		ret := RunIntcode(ints, false)
		if ret == CHECK {
			return 100*noun + verb
			break
		}
	}
	return -1
}

func main() {

	fmt.Println("part 1:", part1())
	fmt.Println("part 2:", part2())
}
