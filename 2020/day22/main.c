#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../lib/llist.h"

#define MAXLINE 16
#define P1  0
#define P2  1

// linked lists for each hand
static node_t *player_1 = NULL;
static node_t *player_2 = NULL;
// globals for length of each list
static int p1_len = 0;
static int p2_len = 0;

int add_cards(node_t *winner, int len)
{
    int total = 0;
    node_t *tmp = winner;
    while (tmp != NULL)
    {
        total += tmp->value * len--;
        tmp = tmp->next;
    }
    return total;
}

void play_cards()
{
    unsigned int p1_hand, p2_hand;
    while (p1_len > 0 && p2_len > 0) {
        // pull top cards of each hand reduce handsize
        p1_hand = pull(&player_1);  p1_len--;
        p2_hand = pull(&player_2);  p2_len--;

        if (p1_hand > p2_hand) {
            append(&player_1, p1_hand); 
            append(&player_1, p2_hand);
            // add length to winner's hand
            p1_len+=2;
        } else {
            append(&player_2, p2_hand);
            append(&player_2, p1_hand);
            p2_len+=2;
        }
    }
}



int main()
{
    int current_player = P1;
    char num[MAXLINE];

    // get each hand into its own linked list
    while(fgets(num, MAXLINE, stdin)) {
        if (current_player == P1) {
            // make sure we only add numbers
            if (strcmp(num, "\n") == 0) continue;
            else if (strstr(num, "Player 1") != NULL) continue;
            else if (strstr(num, "Player 2") != NULL) {
                // player 1 hand done, switch to player 2
                current_player = P2;
                continue;
            } else if (!isalpha(num[0])) {
                append(&player_1, atoi(num));
                p1_len++;
            }
        } else {
            append(&player_2, atoi(num));
            p2_len++;
        }
    }

    // play cards!
    play_cards();

    int total = 0;
    if (p1_len > 0)
        total = add_cards(player_1, p1_len);
    else total = add_cards(player_2, p2_len);

    printf("p1: %d\n", total);


    return 0;
}
