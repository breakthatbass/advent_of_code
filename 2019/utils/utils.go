package utils

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"

	"github.com/muesli/termenv"
)

/* *
* ReadToInts
*
* @desc: read in a file line by line, attempt to atoi each line, save in array
*
* @param: `file` - the file to read.
* @param: `size` - the size to make the array
*
* @return: the array if successful, else error
**/
func ReadToInts(file string, size int) ([]int, error) {
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
