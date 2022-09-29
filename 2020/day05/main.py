INPUT = 'input'

with open(INPUT) as f:
	buf = [line.strip() for line in f.readlines()]

largest_seat = 0
tkts = []

def to_bin(ticket):
    n = 0
    for t in ticket:
        # OR in a 1 if char is 'B' or 'R', else a 0
        n = n << 1 | ((t == 'B') or (t == 'R'))
    return n


def find_my_tkt(tkts):
    tkts = sorted(tkts)
    l = len(tkts)
    for i in range(10, l):
        if tkts[i + 1] != tkts[i] + 1:
            # this means there's a missing tkt, which would be mine
            return tkts[i] + 1
    return 0


for ticket in buf:
    seat = to_bin(ticket)       # convert string to binary
    row = (seat >> 3) & 0x7F    # grab the upper 7 bits
    col = seat & 0x7            # grab the lower 3 bits

    # part 1 - get largest seat number
    seat = row * 8 + col
    if seat > largest_seat:
        largest_seat = seat
    tkts.append(seat)

# part 2
my_seat = find_my_tkt(tkts)

assert largest_seat == 838
assert my_seat == 714
print('part 1:', largest_seat)
print('part 2:', my_seat)
