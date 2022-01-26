#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024
#define MAXFOOD 128
#define MAXWORD 24

struct food {
    char foods[MAXFOOD][MAXWORD];
    char allers[MAXFOOD][MAXWORD];
};

struct food rec_list[MAXFOOD];
int len = 0;

int main()
{
    char buf[MAXLINE];
    char *food_str;
    int i, j;

    i = 0;
    while (fgets(buf, MAXLINE, stdin)) {
        j = 0;
        // break down each food and append to rec_list array
        for (food_str = strtok(buf, " "); food_str[0] != '('; food_str = strtok(NULL, " ")) {
            strcpy(rec_list[i].foods[j++], food_str);
            len++;
        }
        j = 0;
        // break down each allergen and append
        for (food_str = strtok(NULL, ")\n"); food_str != NULL; food_str = strtok(NULL, ")\n")) {
            printf("%s\n", food_str);
        }
        i++;
        j = 0;
    }


    return 0;
}