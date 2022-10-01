INPUT = 'input'
BIT_WIDTH = 12

# take a binary string and convert to int
def stoi(binstr):
    b = 0
    for c in binstr:
        b = b << 1 | (c == '1')
    return b

# get the amount of 1 bits at pos in a list of numbers
def get_one_bits(bins, pos):
    ones = 0
    for b in bins:
        ones += ((b >> pos) & 1)
    return ones

# part 2
def life_suppoert_rating(bins):
    o2_gen_list = bins
    o2_scrub_list = bins
    i = BIT_WIDTH-1
    while i >= 0 and (len(o2_gen_list) > 1 or len(o2_scrub_list) > 1):
        gen_ones = get_one_bits(o2_gen_list, i)
        scrub_ones = get_one_bits(o2_scrub_list, i)
        gen_size = len(o2_gen_list)
        scrub_size = len(o2_scrub_list)

        if not gen_size == 1:
            if (gen_size - gen_ones) > gen_ones:
                o2_gen_list = [b for b in o2_gen_list if not ((b >> i) & 1)]
            else:
                o2_gen_list = [b for b in o2_gen_list if ((b >> i) & 1)]

        if not scrub_size == 1:
            if (scrub_size - scrub_ones) > scrub_ones:
                o2_scrub_list = [b for b in o2_scrub_list if ((b >> i) & 1)]
            else:
                o2_scrub_list = [b for b in o2_scrub_list if not ((b >> i) & 1)]
        i-=1

    return o2_gen_list[0] * o2_scrub_list[0]


# part 1
def power_consumption(bins):
    gamma = 0
    epsilon = 0
    i = BIT_WIDTH-1
    while i >= 0:
        ones = get_one_bits(bins, i)
        if ones > (len(bins) - ones):  # more ones
            gamma |= (1 << i)
        else:  # more zeroes
            epsilon |= (1 << i)
        i -= 1
    return gamma*epsilon


with open(INPUT) as f:
	buf = [stoi(line.strip()) for line in f.readlines()]

part1 = power_consumption(buf)
part2 = life_suppoert_rating(buf)
print('part 1:', part1)
print('part 2:', part2)
assert part1 == 2648450
assert part2 == 2845944