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
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Section struct {
	field string
	value string
}

// validate that the group contains each field in fields array
func validate(group string) int {
	fields := []string{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
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

func CheckHeight(hgt string) bool {
	// get cm or in
	metric := hgt[len(hgt)-2:]
	//fmt.Println("metric", metric)
	// get value
	val, err := strconv.Atoi(hgt[:len(hgt)-2])
	if err != nil {
		return false
	}
	//fmt.Println("val", val)

	if metric == "cm" {
		if val < 150 || val > 193 {
			return false
		}
	} else if metric == "in" {
		if val < 59 || val > 76 {
			return false
		}
	} else {
		return false
	}
	return true
}

func printSections(s []string) {
	for i, sect := range s {
		fmt.Println(i, sect)
	}
	fmt.Println()
}

func extraValidation(group string) int {
	//fmt.Println(group)
	sections := strings.Split(group, " ")
	section := sections[1:] // remove first item, always a blank
	for _, sect := range section {
		//fmt.Println("sections", sect, "len:", len(sect))
		if len(sect) < 3 {
			//fmt.Println("returning")
			return 0
		}
		var s = new(Section)
		s.field = sect[:3]
		s.value = sect[4:]
		//fmt.Println(s.field, s.value)
		switch s.field {
		// birth year
		case "byr":
			n, _ := strconv.Atoi(s.value)
			if n < 1920 || n > 2002 {
				fmt.Println("byr:", s.value, ">", n)
				return 0
			}
		// issue year
		case "iyr":
			n, _ := strconv.Atoi(s.value)
			if n < 2010 || n > 2020 {
				//fmt.Println("iyr:", s.value, ">", n)
				return 0
			}
		// expiration year
		case "eyr":
			n, _ := strconv.Atoi(s.value)
			if n < 2020 || n > 2030 {
				//fmt.Println("eyr:", s.value, ">", n)
				return 0
			}
		// height
		case "hgt":
			// function above
			if !CheckHeight(s.value) {
				//fmt.Println("hgt:", s.value)
				return 0
			}
		// hair color
		case "hcl":
			// a # followed by exactly six characters 0-9 or a-f
			hcolor, _ := regexp.MatchString("^#([0-9]|[a-f]){6}$", s.value)
			if !hcolor {
				//fmt.Println("hcl:", s.value)
				return 0
			}
		case "ecl":
			//fmt.Println("eyecolor", s.value)
			/*
							strcmp(tmp, "amb") && strcmp(tmp, "blu") &&
				                strcmp(tmp, "brn") && strcmp(tmp, "gry") &&
						        strcmp(tmp, "grn") && strcmp(tmp, "hzl") &&
						        strcmp(tmp, "oth")*/
			if s.value != "amb" || s.value != "blu" ||
				s.value != "brn" || s.value != "gry" ||
				s.value != "grn" || s.value != "hzl" ||
				s.value != "oth" {
				//fmt.Println("ecl:", s.value)
				return 0
			}
		case "pid":
			//fmt.Println("pid", s.value)
			if len(s.value) != 9 {
				//fmt.Println("pid:", s.value)
				return 0
			}
		}
	}

	fmt.Println("returning 1")
	return 1
}

func main() {
	valid := 0 // part 1
	extraValid := 0

	scan := bufio.NewScanner(os.Stdin)
	var builder strings.Builder
	var s string

	for scan.Scan() {
		passport := scan.Text()
		if passport == "" { // the line is '\n'
			s = builder.String()
			valid += validate(s)
			//fmt.Println(s, "\n")
			extraValid += extraValidation(s)
			builder.Reset()
		} else {
			builder.WriteRune(' ')
			builder.WriteString(passport)
		}
	}
	// get last group - it gets left out of loop for some reason
	s = builder.String()
	valid += validate(s)
	extraValid += extraValidation(s)

	fmt.Println("part 1:", valid)
	fmt.Println("part 2:", extraValid)
}
