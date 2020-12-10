import re


def makearr(password):
    low = password.split('-')
    high = low[1].split(' ')
    letter = high[1].split(':')
    pw = high[2].split('\n')
    low = int(low[0])
    high = int(high[0])
    letter = letter[0]
    pw = pw[0]
    return low, high, letter, pw

def check_pass(p):
    count = 0
    for i in p[3]:
        if p[2] == i:
            count+=1

    if count < p[0] or count > p[1]:
        return 0
    return 1

def part2(p):
    pw = p[3]
    letter = p[2]
    low = p[0]-1
    high = p[1]-1

    if (pw[low] == letter) ^ (pw[high] == letter):
        return 1
    else: 
        return 0


def main():
    valid = 0
    p2 = 0
    with open('input') as f:
        for line in f:
            pw = makearr(line)
            valid += check_pass(pw)
            p2 += part2(pw)
    f.close()
    print(f'valid password: {valid}')
    print(f'part2: {p2}')
    

main()
