 // compile: go build day06.go util.go
package main

import (
	"fmt"
)

func main() {
	n, _ := ReadInts("inputs/6")
	fish := lanternInit(n)

	for i := 0; i < 80; i++ {
		fish = breed(fish)
	}
	fmt.Println("part 1:", countFish(fish))

	// we already have bred for 80 days
	for i := 0; i < (256-80); i++ {
		fish = breed(fish)
	}
	fmt.Println("part 2:", countFish(fish))
}

// create a map of fish to work with
func lanternInit(fish []int) map[int]int {
	lanterns := make(map[int]int)
	for _, f := range fish {
		lanterns[f]++
	}
	return lanterns
}

// a single day in the ofe of a breeding lantern fish
func breed(fish map[int]int) map[int]int {
	r := make(map[int]int)
	for f, count := range fish {
		if f == 0 {
			r[6] += count		// fish that have passed their timer
			r[8] += count		// new fish
		} else {
			r[f-1] += count
		}
	}
	return r
}

// count up all the living lantern fish
func countFish(fish map[int]int) int {
	total := 0
	for _, f := range fish {
		total += f
	}
	return total
}