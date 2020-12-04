expenses = []
part1 = 0
part2 = 0

with open('input') as f:
    for line in f:
        expenses.append(int(line.rstrip()))

# part1
for num1 in expenses:
    for num2 in expenses:
        n = num1 + num2
        if n == 2020:
            part1 = num1*num2

#part3
for num1 in expenses:
    for num2 in expenses:
        for num3 in expenses:
            n = num1 + num2 + num3
            if n == 2020:
                part2 = num1*num2*num3

print(f'part1: {part1}')
print(f'part2: {part2}')