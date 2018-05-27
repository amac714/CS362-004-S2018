#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//globals
int villageCallFails = 0;
int discardFails = 0;
int actionFails = 0;
int drawCardFails = 0;

void checkVillageCard(int p, struct gameState *post){
    struct gameState pre;
    int effect;
    int bonus = 0;

    //making a copy of the state
    memcpy(&pre, post, sizeof(struct gameState));

    //calling villageCard via cardEffect
    effect = cardEffect(village, 0, 0, 0, post, 0, &bonus);

    if(effect){
        villageCallFails++;
    }

    //draw card
    drawCard(p, &pre);

    if(pre.deckCount[p] != post->deckCount[p]){
        drawCardFails++;
    }

    //+2 actions
    pre.numActions = pre.numActions + 2;

    if(pre.numActions != post->numActions){
        actionFails++;
    }

    //discard card
    discardCard(0, p, &pre, 0);

    if((pre.handCount[p] != post->handCount[p]) && (pre.deckCount[p] != post->deckCount[p])){
        discardFails++;
    }
}

int main(){
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int i, player;
    int itr = 200000;

    printf("***RANDOM TEST***\n");
    printf("TESTING villageCard...\n");

    srand(time(NULL));

    SelectStream(2);
    PutSeed(3);
    
    for(i = 0; i < itr; i++){
        //initializing gameState
        initializeGame(2, k, seed, &G);
        player = floor(Random() * 2);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * (MAX_HAND - 1));
        G.numActions = 1;
        G.whoseTurn = player;

        checkVillageCard(player, &G);
    }

    int totalFails = villageCallFails + drawCardFails + discardFails + actionFails;

    if(totalFails == 0){
        printf("ALL RANDOM TESTS PASSED\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
    }else {
        printf("****RANDOM TESTS RESULTS****\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
        printf("villageCard call tests fails: %d\n", villageCallFails);
        printf("drawCard tests fails: %d\n", drawCardFails);
        printf("discardCard test fails: %d\n", discardFails);
        printf("# of failed actions: %d\n", actionFails);
    }

    return 0;
}