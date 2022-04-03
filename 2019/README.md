## 🎄 Advent of Code 2019 🎄
https://adventofcode.com/2019

My solutions in Go. *In progress...*

### benchmarks
~2015 MacBook Pro 2.7 GHz Dual-Core Intel i5

All benchmarks are done with [hyperfine](https://github.com/sharkdp/hyperfine)

| Day | Time (seconds) | Star(s) |
|-----|----------------|---------|
| 1   | 0.0037         | 🌟🌟    |
| 2   | 0.0103         | 🌟🌟    |

## Intcode Usage:
```Go
func main() {
    // intcode programs need to be int arrays.
    // read in an intcode file into an int array with LoadIntoMemory
    n, err := LoadIntoMemory(FILEPATH)
    if err != nil {
        log.Fatal(err)
    }

    // run the intcode program
    ret := RunIntcode()

    // print the results
    fmt.Println(ret)
}
```
**Compile:**  
```
go build day02.go intcode.go
```