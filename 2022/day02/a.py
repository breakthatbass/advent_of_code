INPUT = 'input'

part_one_score = 0
part_two_score = 0

def part_one(s):
    points = {
    'A X': 4,
    'A Y': 8,
    'A Z': 3,
    'B X': 1,
    'B Y': 5,
    'B Z': 9,
    'C X': 7,
    'C Y': 2,
    'C Z': 6
    }
    return points[s]


def part_two(s):
    points = {
    'A X': 3,
    'A Y': 4,
    'A Z': 8,
    'B X': 1,
    'B Y': 5,
    'B Z': 9,
    'C X': 2,
    'C Y': 6,
    'C Z': 7
    }
    return points[s]


with open(INPUT) as f:
    plays = [line.strip() for line in f.readlines()]

for play in plays:
    part_one_score += part_one(play)
    part_two_score += part_two(play)

print('part 1:', part_one_score)
print('part 2:', part_two_score)

assert part_one_score == 10404
assert part_two_score == 10334