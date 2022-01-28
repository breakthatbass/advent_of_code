package main

import (
	"aoc/day01"
	"aoc/utils"
)

/*
func check_args(args []string) *string {
	if len(args[1:]) != 1 {
		return nil
	} else {
		return &args[1]
	}
}
*/

func main() {
	//poo := check_args(os.Args)

	utils.Greeting()
	day01.Run()
}
