import sys

class Policy:
    def __init__(self, low, high, letter, pw):
        self.low = low
        self.high = high
        self.letter = letter
        self.pw = pw

    def sled(self):
        '''return 1 or 0 whether password is valid according to sled policy'''
        count = 0
        for i in self.pw:
            if self.letter == i:
                count+=1
        if count < int(self.low) or count > int(self.high):
            return 0
        else:
            return 1

    def toboggan(self):
        '''return 1 or 0 whether password is valid according to toboggan policy'''
        low = int(self.low)
        high = int(self.high)

        first = self.letter == self.pw[low-1]
        second = self.letter == self.pw[high-1]

        if first ^ second:
            return 1
        else:
            return 0
            

def parse(s):
    '''parse through string, pull out needed items'''
    s = s.split()
    nums = s[0].split('-')
    low = nums[0]
    high = nums[1]
    letter = s[1][0]
    pw = s[2]
    return low, high, letter, pw


def main():

    valid_sled = 0
    valid_toboggan = 0

    for line in sys.stdin:
        m = parse(line.rstrip())
        p = Policy(m[0], m[1], m[2], m[3])
        valid_sled += p.sled()
        valid_toboggan += p.toboggan()


    print(f'part 1: {valid_sled}')
    print(f'part 2: {valid_toboggan}')

if __name__ == '__main__':
    main()