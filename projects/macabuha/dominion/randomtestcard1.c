#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//global
int smithyCallFails = 0;
int discardFails = 0;
int drawCardFails = 0;
int handCountFails = 0;

void checkSmithyCard(int p, struct gameState *post){
    struct gameState pre;
    int i, effect;
    int bonus = 0;

    //making a copy of the state
    memcpy(&pre, post, sizeof(struct gameState));

    // printf("Bpre.deckCount: %d, post->deckCount: %d\n", pre.deckCount[p], post->deckCount[p]);
    // printf("Bpre.handCount: %d, post->handCount: %d\n", pre.handCount[p], post->handCount[p]);

    //calling smithyCard via cardEffect
    effect = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);

    //check if smithyCard was correctly called
    if(effect){
        smithyCallFails++;
    }

    //smithyCard effects
    //draw 3 cards
    for(i = 0; i < 3; i++){
        drawCard(p, &pre);
    }

    //check for drawCard fails in smithyCard
    if(pre.deckCount[p] != post->deckCount[p]){
        drawCardFails++;
    }

    // printf("pre.deckCount: %d, post->deckCount: %d\n", pre.deckCount[p], post->deckCount[p]);
    // printf("pre.handCount: %d, post->handCount: %d\n", pre.handCount[p], post->handCount[p]);

    //discard card
    discardCard(0, p, &pre, 0);

    //check hand and deck count of pre and post
    if(pre.handCount[p] != post->handCount[p] && pre.deckCount[p] != post->deckCount[p]){
        handCountFails++;
    }


}

int main(){
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int i, player;
    int itr = 200000;

    printf("***RANDOM TEST***\n");
    printf("TESTING smithyCard...\n");

    srand(time(NULL));

    SelectStream(2);
    PutSeed(3);
    
    for(i = 0; i < itr; i++){
        //initializing gameState
        initializeGame(2, k, seed, &G);
        // for(j = 0; j < sizeof(struct gameState); j++){
        //   ((char*)&G)[j] = floor(Random() * 256);
        // }
        player = floor(Random() * 2);
        //printf("player=%d\n", player);
        G.deckCount[player] = floor(Random() * (MAX_DECK - 3));
        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * (MAX_HAND - 3));
        G.whoseTurn = player;

        checkSmithyCard(player, &G);
    }

    int totalFails = smithyCallFails + drawCardFails + discardFails + handCountFails;

    if(totalFails == 0){
        printf("ALL RANDOM TESTS PASSED\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
    }else {
        printf("****RANDOM TESTS RESULTS****\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
        printf("smithyCard call tests fails: %d\n", smithyCallFails);
        printf("drawCard tests fails: %d\n", drawCardFails);
        printf("discardCard test fails: %d\n", discardFails);
        printf("Pre and Post hand/deck count fails: %d\n", handCountFails);
    }

    return 0;
}

