package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)


// convert an array of string ints to int ints
func atoiArray(s []string) []int {
	var a []int

	for _, i := range s {
		n, _ := strconv.Atoi(i)
		a = append(a, n)
	}
	return a
}

// read a string of ints and return an array of ints
func ReadInts(file string) ([]int, error) {
	fp, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	defer fp.Close()

	scanner := bufio.NewScanner(fp)
	scanner.Scan()
	buf := scanner.Text()
	fp.Close()

	s := strings.Split(buf, ",")
	return atoiArray(s), nil
}
