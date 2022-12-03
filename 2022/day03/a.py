INPUT = 'input'

with open(INPUT) as f:
    items = [line.strip() for line in f.readlines()]

priorities = 0

def get_priority(c):
    if c.islower():
        return ((ord(c) - (ord('a'))) + 1)
    return (ord(c) - 38)


for item in items:
    # split strings in half
    item_1 = item[:len(item)//2]
    item_2 = item[len(item)//2:]

    for c in item_1:
        if c in item_2:
            priorities += get_priority(c)
            break

print('part 1:', priorities)
assert priorities > 8109