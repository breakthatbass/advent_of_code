package main

import (
	"aoc/day01"
	"fmt"
	"os"
	"strings"
)

func checkArgs(args []string) *string {

	if len(args[1:]) != 1 {
		return nil
	} else {
		a := strings.TrimRight(args[1], "\n")
		return &a
	}
}

func main() {
	day := checkArgs(os.Args)
	if day == nil {
		fmt.Println("usage: ./aoc day")
		os.Exit(1)
	}

	if strings.Compare(*day, "day01") == 0 {
		day01.Run()
	} else {
		fmt.Printf("error: '%s' not found\n", *day)
		os.Exit(1)
	}
}
