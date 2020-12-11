import sys, math

# part 1
def get_fuel(a):
    i = math.floor(a/3)-2
    return i


def main():
    d = sys.stdin.readlines()
    d = list(map(int, d))

    fuel = []

    for n in d:
        fuel.append(get_fuel(n))
    
    total = sum(fuel)
    print(f'part1 : {total}')
main()

