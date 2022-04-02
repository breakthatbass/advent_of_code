package main

import (
	"bufio"
	"fmt"
	"os"
)

func part1(bins []string) int {
	var gamma int
	var epsilon int

	bits := len(bins[0])
	binlen := len(bins)
	ones := 0

	for i := 0; i < bits; i++ {
		ones = 0
		for j := 0; j < binlen; j++ {

			b := bins[j][i]
			if b == '1' {
				ones++
			}
		}
		if ones > (binlen / 2) {
			gamma = gamma<<1 | 1
			epsilon <<= 1
		} else {
			gamma <<= 1
			epsilon = epsilon<<1 | 1
		}
	}
	return gamma * epsilon
}

func main() {
	var bins []string
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		bins = append(bins, scan.Text())
	}

	fmt.Println("part 1:", part1(bins))

}
