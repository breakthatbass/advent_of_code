INPUT = 'input'
# crate values are located starting at the 2nd char space in the line
# with each following crate value 4 spaces ahead
# e.g.
# space 1 2 3 4 5 6 7 8...
#       [ x ]   [ x ]...
# pile    1       2...
CRATE_VAL_OFFSET = 4

crate_stacks_1 = {} # each entry is a stack of the crate values
crate_stacks_2 = {}

def parse_crate_line(line):
    '''take a line of the crate piles and add any crates to the appropriate entry in crate_piles dict'''
    IN_CRATE = False
    i = 0  # keep track of how many space in to the line we are
    for c in line:
        if IN_CRATE:
            # the pile number of a crate can be determined by this math
            pile = int((i + 1)/CRATE_VAL_OFFSET)
            if pile in crate_stacks_1.keys():
                crate_stacks_1[pile].insert(0, c)
                crate_stacks_2[pile].insert(0, c)
            else:
                crate_stacks_1[pile] = list(c)
                crate_stacks_2[pile] = list(c)
            IN_CRATE = False
        if c == '[':
            IN_CRATE = True
        i += 1

def move_crates(num_to_move, old_pile, new_pile):
    '''move crates from old_pile to new_pile in both stacks'''
    # part 2: get the box stack and move it over to the new pile
    box_stack = crate_stacks_2[old_pile][-num_to_move:]
    del crate_stacks_2[old_pile][-num_to_move:]
    crate_stacks_2[new_pile].extend(box_stack)
    # part 1: move over boxes individually
    while num_to_move > 0:
        n = crate_stacks_1[old_pile].pop()
        crate_stacks_1[new_pile].append(n)
        num_to_move -= 1

def top_crates(crate_stack):
    '''return a string containing all the crates at the top of the stacks'''
    crates = ''
    num_stacks = len(crate_stack)
    for i in range(num_stacks):
        s = crate_stack[i].pop()
        crates += s
    return crates

def main():
    global box_stacks_1
    global box_stacks_2
    with open(INPUT) as f:
        lines = [line.strip('\n') for line in f.readlines()]
    # create the box stacks
    current_line = 0
    while lines[current_line][1] != '1':
        parse_crate_line(lines[current_line])
        current_line += 1
    # passed the crates part, add 2 to current_line to get us to the movement part
    current_line += 2
    # drop all before this point
    lines = lines[current_line:]
    # follow movement directions and move the crates around
    for line in lines:
        line = line.split()
        move_crates(int(line[1]), int(line[3])-1, int(line[5])-1)
    p1 = top_crates(crate_stacks_1)
    p2 = top_crates(crate_stacks_2)
    print('part 1:', p1)
    print('part 2:', p2)

if __name__ == '__main__':
    main()