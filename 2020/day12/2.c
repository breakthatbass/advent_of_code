#include <stdio.h>
#include <stdlib.h>


int main()
{
    char action;
    int units;

    int x = 0;
    int y = 0;
    int wx = 10;
    int wy = -1;
    int turn, tmp, i;

    while (scanf("%c%d\n", &action ,&units) == 2) {
        switch(action) {
            case 'F':
                x += wx * units;
                y += wy * units;
                break;
            case 'N':
                wy -= units;
                break;
            case 'S':
                wy += units;
                break;
            case 'E':
                wx += units;
                break;
            case 'W':
                wx -= units;
                break;
            case 'L':
                i = 0;
                turn = units/90;
                while (i++ < turn) {
                    tmp = wx;
                    wx = wy;
                    wy = -tmp;
                }
                break;
            case 'R':
                i = 0;
                turn = units/90;
                while (i++ < turn) {
                    tmp = wx;
                    wx = -wy;
                    wy = tmp;
                }
                break;
            default:
                fprintf(stderr, "something broke!\n");
                exit(1);
        }
    }

    int total = abs(x)+abs(y);
    printf("part 2: %d\n", total);
    return 0;
}