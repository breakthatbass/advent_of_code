#include <stdio.h>
#include <stdlib.h>


int main()
{
    char action;
    int units;
    char directions[4] = {'N', 'E', 'S', 'W'};

    int x = 0;      // east/west moves
    int y = 0;      // north/south moves
    int dir = 1;    // start facing east
    int turn;

    while (scanf("%c%d\n", &action ,&units) == 2) {
        if (action == 'F') action = directions[dir];
        switch(action) {
            case 'N':
                y -= units;
                break;
            case 'S':
                y += units;
                break;
            case 'E':
                x += units;
                break;
            case 'W':
                x -= units;
                break;
            case 'L':
                dir = (dir + 4 - units / 90) % 4;
                break;
            case 'R':
                dir = (dir + units / 90) % 4;
                break;
            default:
                fprintf(stderr, "something broke!\n");
                exit(1);
        }
    }

    int total = abs(x)+abs(y);  // no clue wh
    printf("part 1: %d\n", total);
    return 0;
}