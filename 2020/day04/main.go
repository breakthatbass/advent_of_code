/**
 * day 04 2020
 * https://adventofcode.com/2020/day/4
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"bufio"
	"os"
	"fmt"
	"strings"
)

var fields = []string{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}

func validate(group string) int {
	fieldCount := 0
	for _, field := range fields {
		if strings.Contains(group, field) {
			fieldCount++
		}
	}
	if fieldCount == 7 {
		return 1
	}
	return 0
}


func main() {
	valid := 0 // part 1
	scan := bufio.NewScanner(os.Stdin)
	var builder strings.Builder

 	for scan.Scan() {
 		line := scan.Text()
		if line == "" {
			// end of section
			valid += validate(builder.String())
			builder.Reset()
		} else {
			builder.WriteString(line)
		}
 	}
	// get last group - it gets left out of loop for some reason
	valid += validate(builder.String())
	fmt.Println("part 1:", valid)
}