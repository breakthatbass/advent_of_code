package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var depth int
var depthPart2 int
var hpos int
var aim int

func parseLine(line string) (string, int) {
	v := strings.Split(line, " ")
	n, _ := strconv.Atoi(v[1])
	return v[0], n
}

func handleDirections(instr string, val int) {

	switch instr {

	case "forward":
		hpos += val
		depthPart2 += (aim * val)
	case "up":
		depth -= val
		aim -= val
	case "down":
		depth += val
		aim += val
	default:
		fmt.Printf("unrecognized option: %s\n", instr)
	}
}

func main() {
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		line := scan.Text()
		s, n := parseLine(line)
		handleDirections(s, n)
	}

	fmt.Println("part 1:", depth*hpos)
	fmt.Println("part 2:", depthPart2*hpos)
}
