INPUT = 'input'

class Intcode:
    def __init__(self, code):
        self.code = code
        self.ADD = 1
        self.MULT = 2
        self.STORE = 3
        self.OUT = 4
        self.STOP = 99

    def run(self):
        '''run the code through the intcode interpreter'''
        i = 0
        while i < len(self.code):
            opcode = self.code[i]
            input1 = self.code[i+1]
            input2 = self.code[i+2]
            output = self.code[i+3]

            print(f'OP: {opcode}, IN1: {input1}, IN2: {input2}, OUT: {output}')

            if opcode == self.ADD:
                self.code[output] = self.code[input1] + self.code[input2]
            elif opcode == self.MULT:
                self.code[output] = self.code[input1] * self.code[input2]
            elif opcode == self.STOP:
                print()
                print(self.code)
                return self.code[0]
            else:
                print(f'error: {opcode}: unknown opcode')
            i+=4
        return None


with open(INPUT) as fp:
        code = [int(n) for n in fp.readline().strip().split(',')]
# restore 1202 alarm
code[1] = 12
code[2] = 2
intcode = Intcode(code)

part1 = intcode.run()
print(part1)