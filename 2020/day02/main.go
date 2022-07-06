package main

import (
	"bufio"
	"os"
	"fmt"
	"strings"
)

func sled(min int, max int, c byte, pass string) int {
	count := 0
	for i, _ := range pass {
		if pass[i] == c {
			count++
			i++
		}
	}
	if count >= min && count <= max {
		return 1
	}
	return 0
}

func toboggan(min int, max int, c byte, pass string) int {
	if (pass[min-1] == c) != (pass[max-1] == c) {
		return 1
	}
	return 0
}

func main() {

	var (
		min int
		max int
		c byte
		pass string
	)

	validSled := 0
	validToboggan := 0

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		f := strings.NewReader(scan.Text())

		fmt.Fscanf(f, "%d-%d %c: %s", &min, &max, &c, &pass)
		validSled += sled(min, max, c, pass)
		validToboggan += toboggan(min, max, c, pass)
	}
	fmt.Println("part 1:", validSled)
	fmt.Println("part 2:", validToboggan)
}