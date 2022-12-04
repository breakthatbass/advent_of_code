INPUT = 'input'

with open(INPUT) as f:
    sections = [line.strip().split(',') for line in f.readlines()]

part_1_total = 0
part_2_total = 0

def do_they_overlap(range_1, range_2):
    '''part 1: check of either of the range are contained within the other'''
    if sec_1[0] in range_2 and sec_1[1] in range_2:
        return 1
    if sec_2[0] in range_1 and sec_2[1] in range_1:
        return 1
    return 0


def num_of_overlaps(range_1, range_2):
    '''part 2: do any values in the ranges overlap?'''
    b = [n for n in range_1]
    for n in range_2:
        if n in b:
            return 1
    return 0


for sec in sections:
    sec_1 = [int(i) for i in sec[0].split('-')] 
    sec_2 = [int(i) for i in sec[1].split('-')]
    part_1_total += do_they_overlap(range(sec_1[0], (sec_1[1]+1)), range(sec_2[0], (sec_2[1]+1)))
    part_2_total += num_of_overlaps(range(sec_1[0], (sec_1[1]+1)), range(sec_2[0], (sec_2[1]+1)))

print('part 1:', part_1_total)
print('part 2:', part_2_total)