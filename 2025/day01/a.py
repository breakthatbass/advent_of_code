INPUT = 'input.txt'

with open(INPUT) as f:
    turns = [line.strip() for line in f.readlines()]

dial = 50
part1 = 0
part2 = 0

for turn in turns:
    direction = turn[0]
    moves = int(turn[1:])

    if dial == 0:
        part1 += 1

    # Handle part 2
    if direction == 'L':
        part2 += abs(dial - moves) // 100 + (dial != 0 and dial <= moves)
    else: # R
        part2 += (dial + moves) // 100

    tmp = (dial - moves) if direction == 'L' else (dial + moves)
    dial = tmp % 100

print('part 1:', part1)
print('part 2:', part2)
