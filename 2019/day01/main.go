package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
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

func readToInts(file string, size int) ([]int, error) {
	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}

	i := 0
	values := make([]int, size)

	scanner := bufio.NewScanner(f)

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return values, err
		}
		values[i] = val
		i++
	}
	return values, scanner.Err()
}

func Run() {
	n, err := readToInts("input", 100)
	if err != nil {
		log.Fatal(err)
	}

	mass, biggermass := getMass(n)

	fmt.Println("part 1:", mass)
	fmt.Println("part 2:", biggermass)
}

func main() {
	Run()
}
