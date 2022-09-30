INPUT = 'input'
BIT_WIDTH = 12

# take a binary string and convert to int
def stoi(binstr):
    b = 0
    for c in binstr:
        b = b << 1 | (c == '1')
    return b

def power_consumption(bins):
    gamma = 0
    epsilon = 0
    i = BIT_WIDTH-1
    while i >= 0:
        ones = 0
        for bin in bins:
            ones += ((bin >> i) & 1)

        if ones > (len(bins) - ones):
            gamma |= (1 << i)
        else:
            epsilon |= (1 << i)   
        i -= 1
    return gamma*epsilon


with open(INPUT) as f:
	buf = [stoi(line.strip()) for line in f.readlines()]

n = power_consumption(buf)
print('part 1:', n)