#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "llist.h"

// globals for length of each list
int p1_len = 0;
int p2_len = 0;

#define MAXLINE 16
#define P1  0
#define P2  1



void play_cards(node_t *l1, node_t *l2)
{
    int p1_hand, p2_hand;
    int i = 0;
    while (p1_len > 0 && p2_len > 0) {

        // pull top cards of each hand reduce handsize
        p1_hand = pull(&l1);  p1_len--;
        p2_hand = pull(&l2);  p1_len--;

        if (p1_hand > p2_hand) {
            append(&l1, p1_hand); 
            append(&l1, p2_hand);
            // add length to winner's hand
            p1_len+=2;
        } else {
            append(&l2, p2_hand);
            append(&l2, p1_hand);
            p2_len+=2;
        }
    }
    printf("player 1: %d cards\n", p1_len);
    printlist(l1);
    printf("player 2: %d cards\n", p2_len);
    printlist(l2);
}

int main()
{
    int current_player = P1;
    char num[MAXLINE];

    node_t *player_1 = NULL;
    node_t *player_2 = NULL;

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
    play_cards(player_1, player_2);

    

    return 0;
}