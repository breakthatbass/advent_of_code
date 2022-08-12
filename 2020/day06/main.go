package main

import (
	"fmt"
	"bufio"
	"os"
)

func countYes(s string) int {
	n := map[rune]int{}
	for _, c := range s {
		n[c]++;
	}
	return len(n)
}

func countChars(s string, c rune) int {
	count := 0
	for _, b := range s {
		if c == b {
			count++
		}
	}
	return count
}

func allYes(s string, people int) int {
	total := 0
	chars := 0
	for _, c := range s {
		chars = countChars(s, c)
		if chars == people {
			total++
		}
	}
	return total
}

func main() {
	
	var group string
	var people int

	part1 := 0
	part2 := 0
	
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		buf := scan.Text()
		if buf != "" {
			people++
			group += buf
		} else {
			part1 += countYes(group)
			part2 += allYes(group, people)
			// reset
			people = 0
			group = ""
		}
	}
	part1 += countYes(group)
	part2 += allYes(group, people)

	// part 2 bugged
	fmt.Println("part 1:", part1)
	fmt.Println("part 2:", part2)
}
