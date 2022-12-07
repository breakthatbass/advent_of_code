INPUT = 'input'

with open(INPUT) as f:
    d = f.readline().strip()

PART1_MSG_SIZE = 4
PART2_MSG_SIZE = 14
part_1_found = False
part_2_found = False

for c in range(len(d)):
    if not part_1_found:
        msg_1 = [d[i] for i in range(c, c + PART1_MSG_SIZE)]
        if len(set(msg_1)) == PART1_MSG_SIZE:
            part_1 = c + PART1_MSG_SIZE
            part_1_found = True
    if not part_2_found:
        msg_2 = [d[i] for i in range(c, c + PART2_MSG_SIZE)]
        if len(set(msg_2)) == PART2_MSG_SIZE:
            part_2 = c + PART2_MSG_SIZE
            part_2_found = True
    if part_1_found and part_2_found:
        break

print('part 1:', part_1)
print('part 2:', part_2)