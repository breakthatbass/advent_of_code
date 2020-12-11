import sys, math

# part 1
def get_fuel(a):
    i = math.floor(a/3)-2
    return i

#part 2
def more_fuel(a):
    mf = []
    while a > 0:
        a = get_fuel(a)
        if a < 0:
            a = 0
        mf.append(a)
    return sum(mf)


def main():
    fp = open('input').readlines()
    fp =list(map(int, fp))

    fuel = []

    for n in fp:
        fuel.append(get_fuel(n))
    
    total = sum(fuel)
    print(f'part1: {total}')

    for n in fuel:
        total+=more_fuel(n)

    print(f'part2: {total}')

main()

