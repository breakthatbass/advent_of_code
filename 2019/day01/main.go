package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func assert(a int, b int) {
	if a != b {
		s := fmt.Sprintf("error: %d != %d\n", a, b)
		log.Fatal(s)
	}
}

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

func main() {
	fp, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer fp.Close()

	scanner := bufio.NewScanner(fp)

	total := 0
	total2 := 0

	for scanner.Scan() {
		line, err := strconv.Atoi(scanner.Text())
		if err != nil {
			log.Fatal(err)
		}
		mass := ((line / 3) - 2)
		total += mass
		total2 += part2(line)
	}

	fmt.Println("part 1:", total)
	fmt.Println("part 2:", total2)
	assert(total, 3371958)
	assert(total2, 5055050)
}
