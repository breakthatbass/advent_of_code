INPUT = 'input'
BIT_WIDTH = 12

# take a binary string and convert to int
def stoi(binstr):
    b = 0
    for c in binstr:
        b = b << 1 | (c == '1')
    return b

def o2_gen_rating(bins):
    i = BIT_WIDTH-1
    while i >= 0 and len(bins) > 1:
        ones = 0
        zeroes = 0
        for b in bins:
            # get the number of ones in the list at bit i
            ones += ((b >> i) & 1)
        zeroes = len(bins) - ones
        if zeroes > ones:
            bins = [b for b in bins if not ((b >> i) & 1)]
        else:
            # more ones or equal amount of ones and zeroes
            bins = [b for b in bins if ((b >> i) & 1)]
        i-=1
    # should be only a single element left in list at this point
    return bins[0]

def o2_scrub_rating(bins):
    i = BIT_WIDTH-1
    while i >= 0 and len(bins)> 1:
        ones = 0
        zeroes = 0
        for b in bins:
            # get the number of ones in the list at bit i
            ones += ((b >> i) & 1)
        zeroes = len(bins) - ones
        if zeroes > ones:
            bins = [b for b in bins if ((b >> i) & 1)]
        else:
            # more ones or equal amount of ones and zeroes
            bins = [b for b in bins if not ((b >> i) & 1)]
        i-=1
    # should be only a single element left in list at this point
    return bins[0]

# part 1
def power_consumption(bins):
 
    gamma = 0
    epsilon = 0
    i = BIT_WIDTH-1
    while i >= 0:
        ones = 0
        for b in bins:
            ones += ((b >> i) & 1)
        if ones > (len(bins) - ones):
            # more ones
            gamma |= (1 << i)
        else:
            # more zeroes
            epsilon |= (1 << i)
        i -= 1
    return gamma*epsilon


with open(INPUT) as f:
	buf = [stoi(line.strip()) for line in f.readlines()]

part1 = power_consumption(buf)

part2 = o2_gen_rating(buf) * o2_scrub_rating(buf)
print('part 1:', part1)
print('part 2:', part2)

assert part1 == 2648450
assert part2 == 2845944