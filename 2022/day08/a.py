import pytest

INPUT = 'input'

with open(INPUT) as f:
    trees = [tree.strip() for tree in f.readlines()]


def print_forest(trees):
    row = 1
    while row < len(trees)-1:
        for col in range(1, 4):
            print(trees[row][col], end=' ')
        row += 1
        print()

def look_up(row, col):
    t = []
    while row > 0:
        row -= 1
        t.append(trees[row][col])
    return t

def look_down(row, col):
    t = []
    while row < (len(trees)-1):
        row += 1
        t.append(trees[row][col])
    return t

def look_right(row, col):
    t = []
    while col < (len(trees[0])):
        col += 1
        try:
            t.append(trees[row][col])
        except:
            return t
    return t


def look_left(row, col):
    t = []
    while col > 0:
        col -= 1
        try:
            t.append(trees[row][col])
        except:
            return t
    return t


def check_trees(tree, tree_list):
    if not tree_list == None:
        for t in tree_list:
            if int(tree) <= int(t):
                return False
    return True


def is_it_visible(row, col):
    n = int(trees[row][col])
    if check_trees(n, look_up(row, col)):
        return 1 
    if check_trees(n, look_down(row, col)):
        return 1
    if check_trees(n, look_left(row, col)):
        return 1
    if check_trees(n, look_right(row, col)):
        return 1
    return 0


def get_viewing_distance(tree, tree_list):
    n = 0
    if not tree_list == None:
        for t in tree_list:
            print(f'{t} ', end='')
            if int(tree) > int(t):
                n += 1
            elif int(tree) == int(t):
                n += 1
                break
            else:
                n+=1
                break
    print(f'({n}), ', end='')
    return n

max_score = 0

def get_scenic_score(row, col):
    global max_score
    n = int(trees[row][col])
    print(f'{n}: ', end='')
    v1 = get_viewing_distance(n, look_up(row, col))
    v2 = get_viewing_distance(n, look_down(row, col))
    v3 = get_viewing_distance(n, look_left(row, col))
    v4 = get_viewing_distance(n, look_right(row, col))
    scenic_score = v1 * v2 * v3 * v4
    print(f' --> score: {scenic_score}')
    if scenic_score > max_score:
        max_score = scenic_score


def count_visible_trees(trees):
    row = 1
    visible_trees = 0
    while row < len(trees)-1:
        for col in range(1, len(trees[0])-1):
            #print(trees[row][col], end=' ')
            n = is_it_visible(row, col)
            visible_trees += n
            get_scenic_score(row, col)
        row += 1
    return visible_trees

part1_total = (count_visible_trees(trees) + (len(trees)*2) + ((len(trees[0])-2)*2))
print('part 1:', part1_total)
print('part 2:', max_score)


#################################################
# TESTS                                         #
#################################################

@pytest.mark.parametrize(
    "row, col, visible_trees",
    [(4, 3, ['4', '3', '1', '7']),
    (1, 3, ['7']),
    (0, 3, []),
    (0, 0, []),
    (2, 4, ['2', '3'])]
)
def test_look_up(row, col, visible_trees):
    t = look_up(row, col)
    assert t == visible_trees
 
@pytest.mark.parametrize(
    "row, col, visible_trees",
    [(0, 0, ['2', '6', '3', '3']),
    (1, 3, ['3', '4', '9'])]
)
def test_look_down(row, col, visible_trees):
    t = look_down(row, col)
    assert t == visible_trees


@pytest.mark.parametrize(
    "row, col, visible_trees",
    [(0, 0, ['0', '3', '7', '3']),
    (1, 3, ['2']),
    (4, 4, [])]
)
def test_look_right(row, col, visible_trees):
    t = look_right(row, col)
    assert t == visible_trees


@pytest.mark.parametrize(
    "row, col, visible_trees",
    [(0, 4, ['7', '3', '0', '3']),
    (1, 3, ['5', '5', '2']),
    (0, 0, [])]
)
def test_look_left(row, col, visible_trees):
    t = look_left(row, col)
    assert t == visible_trees


@pytest.mark.parametrize(
    "tree, tree_list, bool",
    [(0, [1, 4, 5, 6], False),
    (6, [], True), 
    (9, [1, 2, 3, 4, 5, 6, 1, 2, 3, 4], True), 
    (3, ['2', '1'], True),
    (1, ['5', '2', '8'], False), 
    (0, [], True)]
)
def test_check_trees(tree, tree_list, bool):
    assert check_trees(tree, tree_list) == bool
