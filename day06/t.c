
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char *s = "abcdefgbdef";

    int total = 0;
    char *tmp = malloc(sizeof(char)*15);
    strcpy(tmp, s);
    int len = strlen(s);
    tmp[len] = '\0';

    while (*s) {
        char t = *s;
        s++;
        if (strchr(s, t) != NULL) {
            printf("%c found in %s\n", *s, tmp);
            *s = '\n';
            total++;
            //s++;
        }
    }
    printf("total: %d\n", total);
    return 0;
}