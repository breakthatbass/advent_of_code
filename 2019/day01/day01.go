package day01

import (
	"aoc/utils"
	"fmt"
	"log"
)

func part2(mass int) (total int) {
	total = 0
	for mass > 0 {
		mass = ((mass / 3) - 2)
		if mass < 0 {
			mass = 0
		}
		total += mass
	}
	return total
}

func getMass(n []int) (int, int) {
	total := 0
	total2 := 0
	l := len(n)
	for i := 0; i < l; i++ {
		mass := ((n[i] / 3) - 2)
		total += mass
		total2 += part2(n[i])
	}
	return total, total2
}

func Run() {
	n, err := utils.ReadToInts("day01/input", 100)
	if err != nil {
		log.Fatal(err)
	}

	mass, biggermass := getMass(n)

	fmt.Println("part 1:", mass)
	fmt.Println("part 2:", biggermass)
}
