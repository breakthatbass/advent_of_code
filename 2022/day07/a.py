INPUT = 'input'

TOTAL_DISK_SPACE = 70000000
SPACE_NEEDED = 30000000
PART_1_TARGET_SIZE = 100000
PART_2_TARGET_SIZE = 8381165

with open(INPUT) as f:
    cmds = [line.strip() for line in f.readlines()]

class File:
    def __init__(self, fname, fsize):
        self.fname = fname
        self.fsize = fsize

class Dir:
    def __init__(self, dname, parent=None):
        self.dname = dname
        self.parent = parent
        self.files = []
        self.children = []
        self.total_size = 0
    
    def add_to_size(self, size):
        self.total_size += size
        if self.parent:
            self.parent.add_to_size(size)

    def add_file(self, f):
        self.files.append(f)
        self.add_to_size(f.fsize)


root_dir = Dir('/')
current_dir = root_dir

for cmd in cmds:
    argv = cmd.split()
    if argv[0] == '$':
        # command
        if argv[1] == 'cd':
            if argv[2] == '..':
                # move up
                current_dir = current_dir.parent
            else:
                for c in current_dir.children:
                    if c.dname == argv[2]:
                        current_dir = c
    elif argv[0] == 'dir':
        d = Dir(argv[1], current_dir)
        current_dir.children.append(d)
    else:
        f = File(argv[1], int(argv[0]))
        current_dir.add_file(f)

part_1_dirs = []
part_2_dirs = []

space_needed = SPACE_NEEDED - (TOTAL_DISK_SPACE - root_dir.total_size)

def find_dirs_part_1(dir):
    if dir.total_size <= PART_1_TARGET_SIZE:
        part_1_dirs.append(dir.total_size)
    for child in dir.children:
        find_dirs_part_1(child)

def find_dirs_part_2(dir):
    if dir.total_size >= space_needed:
        part_2_dirs.append(dir.total_size)
    for child in dir.children:
        find_dirs_part_2(child)

find_dirs_part_1(root_dir)
find_dirs_part_2(root_dir)
print('part 1:', sum(part_1_dirs))
print('part 2:', sorted(part_2_dirs)[0])