#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <advent.h>

#define MAXLINE 256

char **bag_list;
unsigned long bag_list_len = 0;

struct bag {
    char *bag_name;
    char *bag1;
    char *bag2;
    char *bag3;
    char *bag4;
    struct bag *next;
}; typedef struct bag bag;


bag parse_bags(char *buf)
{
    int i;
    char *bag_adj, *bag_col, *bag_name, *bufcpy;

    // make copy of buf so we can mutilat the copy not buf
    bufcpy = malloc(sizeof(char)*strlen(buf));
    strcpy(bufcpy, buf);

    buf = strstr(buf, "contain");
    
    // parse to get bag_name
    bag_adj = strtok(bufcpy, " ");
    bag_col = strtok(NULL, " ");
    bag_name = malloc(sizeof(char)*(strlen(bag_adj)+strlen(bag_col))+1);
    strcat(bag_name, bag_adj);
    strcat(bag_name, " ");
    strcat(bag_name, bag_col);

    // load into struct
    bag tmp;
    tmp.bag_name = bag_name;
    tmp.holds = buf;

    return tmp;
}


int main(int argc, char **argv)
{
    arg_check(argc);
    char *file = argv[1];
    int len = count_lines(file);
    FILE *fp = file_ptr(file);   

    char buf[MAXLINE];

    bag_list = init_str_arr(len, MAXLINE);

    int c; 
    int i = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '.') {
            
            bag cur = parse_bags(buf);
            if (strstr(cur.holds, "shiny gold") != NULL) {
                bag_list[bag_list_len++] = cur.bag_name;
            }
            memset(buf, 0, MAXLINE);
            i=0;
        } else buf[i++] = c;
    } 


    for (i = 0; i < bag_list_len; i++) 
        printf("%s\n", bag_list[i]);

    fclose(fp);
    return 0;
}

