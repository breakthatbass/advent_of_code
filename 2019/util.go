package main

import (
	"bufio"
	"os"
	"strconv"

	"github.com/muesli/termenv"
)

/**
 * ReadInts
 *
 * @desc: read in lines from stdin and convert to ints
 *
 * @return: array of ints
 *
 * this functions expects actual ints coming in
 * as is a typical puzzle input in AoC
 *
 * @usage: ./exe < input-file
 **/
func ReadInts() []int {
	var n []int
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		line, _ := strconv.Atoi(scan.Text())
		n = append(n, line)
	}
	return n
}

/**
 * ColorStr
 *
 * @desc: colorize `s` with `hex` color.
 *
 * @param: `s` string to colorize.
 * @param: `hex` hex color
 *
 * @return: `s` colored with `hex`.
 **/
func ColorStr(s string, hex string) termenv.Style {
	p := termenv.ColorProfile()
	return termenv.String(s).Foreground(p.Color(hex))
}
