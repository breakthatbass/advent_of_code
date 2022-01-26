## --- Day 7: Handy Haversacks ---

This one was pretty tough. Using C for this didn't make it any easier. It was fun and very rewarding once I got it properly working. And the trick for today? Recursion. Which I'm not totally comfortable with yet.

I got some help from this awesome [article](https://auth0.com/blog/advent-of-code-tips-tricks/).  

Getting the right data structure is the crux of planning out any program. If you get the right data structure, everything else falls into place. I came up with a linked list where each node represented a bag and also had an array of a sub_bag node which contains all of the sub bags. And it also has a head pointer.

The list is in the [lib](https://github.com/breakthatbass/advent_of_code2020/tree/main/day07/lib) directory.


### Linked list Visualization
```
 List                 Bag node
 ___________          ________________
| head *ptr | -----> | bag name      |          index: 0            index: 1
|-----------|        |---------------|          ______________________________________
| list size |        | sub bag array | ---->   | bag: "shiny gold"| bag: "faded blue"|
|__________ |        |---------------|         |------------------|------------------|
                     | # of sub bags |         | count: 2         | count: 1         |
                     |---------------|         |__________________|__________________|
                     | next bag *ptr |
                     |_______________| ----------------------------------------------------> bag node...
```

### Usage
Like all the others it takes input through `stdin`.

```
make

./bags < input
```