import sys

part1 = 0
part2 = 0

nums = sys.stdin.readlines()
nums = list(map(int, nums))

# part1
for num1 in nums:
    for num2 in  nums:
        n = num1 + num2
        if n == 2020:
            part1 = num1*num2

#part2
for num1 in nums:
    for num2 in nums:
        for num3 in nums:
            n = num1 + num2 + num3
            if n == 2020:
                part2 = num1*num2*num3

print(f'part1: {part1}')
print(f'part2: {part2}')
