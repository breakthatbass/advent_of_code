INPUT = 'input'

with open(INPUT) as f:
    cals = [line for line in f.readlines()]

current_elf = 0
all_elf_calories = []

for cal in cals:
    if cal == '\n':
        # done with the current elf - add it to the list
        all_elf_calories.append(current_elf)
        current_elf = 0
    else:
        current_elf += int(cal.strip())

# sort the list of elf calories in descending order
all_elf_calories.sort(reverse=True)
# grab the first three elements...which are the top three largest values
top_three_elves = all_elf_calories[0] + all_elf_calories[1] + all_elf_calories[2]

print('part 1:', all_elf_calories[0])
print('part 2:', top_three_elves)
