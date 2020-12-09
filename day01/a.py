import sys
import itertools as it

part1 = 0
part2 = 0

nums = sys.stdin.readlines()    # cat input | python a.py
nums = list(map(int, nums))     # convert all to ints, strip \n

# part 1
for a, b in it.combinations(nums, 2):
    if a+b == 2020:
        part1 = a*b
        break

# part 2
for a,b,c in it.combinations(nums, 3):
    if a+b+c == 2020:
        part2 = a*b*c
        break

print(f'part1: {part1}')
print(f'part2: {part2}')
