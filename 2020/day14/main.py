import re

INPUT = 'input'

memory = {}

with open(INPUT) as f:
	buf = [line.strip() for line in f.readlines()]

for line in buf:
	if line[1] == 'a': # bitmask line
		# reset masks
		mask_and = 0
		mask_or = 0
		# make new masks
		for b in line[7:]:  # leave out the 'mask = ' part
			mask_and = (mask_and << 1) | (b == 'X')
			mask_or = (mask_or << 1) | (b == '1')
	else:
		# we have a line with a memory address and value
		r = re.compile('\[(.*?)\]')
		buf = r.split(line)
		addr = int(buf[1])
		# strip \n and drop chars 0-2 which is the ' = '
		val = int(buf[2][2:])
		val = (val & mask_and) | mask_or
		# add or overwrite memory value
		memory[addr] = val

part1 = sum(memory.values())
print('part 1:', part1)
