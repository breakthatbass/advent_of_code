INPUT = 'input'

with open(INPUT) as f:
    items = [line.strip() for line in f.readlines()]


def get_priority(c):
    '''get the priority of a char'''
    if c.islower():
        return ((ord(c) - (ord('a'))) + 1)
    return (ord(c) - 38)


def elf_groups(groups):
    '''find the common char in all 3 elf groups and return the priority of it'''
    for c in groups[0]:
        if c in groups[1] and c in groups[2]:
            return get_priority(c)
    return 0

def part_2():
    priorities = 0
    groups = [] # hold up to three elf groups at a time
    for item in items:
        groups.append(item)
        if len(groups) == 3:
            priorities += elf_groups(groups)
            groups.clear()
    return priorities


def part_1():
    priorities = 0
    for item in items:
        # split strings in half
        item_1 = item[:len(item)//2]
        item_2 = item[len(item)//2:]

        for c in item_1:
            if c in item_2:
                priorities += get_priority(c)
                break
    return priorities

print('part 1:', part_1())
print('part 2:', part_2())