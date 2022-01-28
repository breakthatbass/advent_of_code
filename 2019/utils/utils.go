package utils

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"

	"github.com/muesli/termenv"
)

func file_path(pkg string) (*string, error) {
	pre, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
		return nil
	}
	full_path := fmt.Sprintf("%s/%s/input", pre, pkg)
	return &full_path
}

func ReadToInts(file string) ([]int, error) {
	path := file_path(day string) 

	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(f)
	values := []int{}
	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return values, err
		}
		values = append(values, val)
	}
	return values, scanner.Err()
}

func Greeting() {
	p := termenv.ColorProfile()

	welcome := termenv.String("Welcome to")
	adv := termenv.String("Advent of Code")
	year := termenv.String("2019!")

	welcome = welcome.Foreground(p.Color("#D03B47"))
	adv = adv.Foreground(p.Color("#F2F3F8"))
	year = year.Foreground(p.Color("#5CB69B"))

	greeting := fmt.Sprintf("%s %s %s\n", welcome, adv, year)

	fmt.Println(greeting)
}
