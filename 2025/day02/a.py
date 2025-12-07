import textwrap
from itertools import groupby

INPUT = 'input.txt'

with open(INPUT) as f:
    ranges = f.readline()

ranges = ranges.split(',')


def part1(start, end):
    invalids = 0
    for id in range(start, (end + 1)):
        id_str = str(id)
        half = int(len(id_str) / 2)
        # Break in half and grab each side
        side1 = id_str[:half]
        side2 = id_str[half:]
        # If each side is equal, it's a repeated sequence
        if side1 == side2:
            invalids += id
    return invalids


def part2(start, end):
    # TODO: part 2 is very slow
    invalid_total = 0
    for id_ in range(start, (end + 1)):
        id_str = str(id_)
        i = 1
        while True:
            if i >= len(id_str):
                break
            id_list = textwrap.wrap(id_str, i)
            if len(id_list[0]) != len(id_list[-1]):
                i += 1
                break
            if len(set(id_list)) == 1:
                print('\t--> found invalid:', id_str)
                invalid_total += int(id_str)
                break
            i += 1
    return invalid_total



part1_inv = 0
part2_inv = 0
for r in ranges:
    start, end = r.split('-')
    print(f'NEW RANGE: {start} -- {end}')
    part1_inv += part1(int(start), int(end))
    part2_inv += part2(int(start), int(end))


assert part1_inv == 40398804950
assert part2_inv == 65794984339
print('part 1:', part1_inv)
print('part 2:', part2_inv)
