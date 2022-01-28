package day01

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func file_path(pkg string) *string {
	pre, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
		return nil
	}
	full_path := fmt.Sprintf("%s/%s/input", pre, pkg)
	return &full_path
}

func Run() {
	f_path := file_path("day01")

	fp, err := os.Open(*f_path)
	if err != nil {
		log.Fatal(err)
		return
	}
	defer fp.Close()

	scanner := bufio.NewScanner(fp)
	total := 0

	for scanner.Scan() {
		line, err := strconv.Atoi(scanner.Text())
		if err != nil {
			log.Fatal(err)
		}
		mass := ((line / 3) - 2)
		total += mass

	}

	fmt.Println("part 1:", total)

}
