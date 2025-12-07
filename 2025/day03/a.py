INPUT = 'test_input.txt'

with open(INPUT) as f:
    banks = [line.strip() for line in f.readlines()]

total_joltage_part1 = 0

def get_max_digit_and_index(bank, ignore_last_digit=False):
    largest = 0
    index = 0
    bank_iter = bank[:-1] if ignore_last_digit else bank
    for i, digit in enumerate(bank_iter):
        if int(digit) > largest:
            largest = int(digit)
            index = i
    return (largest, index)

def part1(bank):
    max_dig = 0
    max_dig_i = 0
    print(bank)
    
    max_digit, max_index = get_max_digit_and_index(bank, ignore_last_digit=True)
    other_largest, _ = get_max_digit_and_index(bank[max_index + 1:])
    joltage = int(f'{max_digit}{other_largest}')
    print('\t--> total joltage:', joltage)
    return joltage

def part2():
    pass

for bank in banks:
    total_joltage_part1 += part1(bank)
assert total_joltage_part1 == 16993
print(total_joltage_part1)


        
    