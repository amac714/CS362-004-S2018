#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//globals for fail checks
int adventurerCardFails = 0;
// int treasureDrawFails = 0;
int drawCardFails = 0;
int shuffleFails = 0;
int discardFails = 0;

void checkAdventurerCard(int p, struct gameState *post){
    struct gameState pre;
    int cardDrawn, treasure;
    int temphand[MAX_HAND];
    int drawntreasure = 0;
    int z = 0;
    int bonus = 0;
    int effect, sRes;
    int preCoins = 0, postCoins = 0;
    int goldDiscards = 0, silverDiscards = 0, copperDiscards = 0;

    //making a copy of the state
    memcpy(&pre, post, sizeof(struct gameState));

    //calling adventurerCard via cardEffect
    effect = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);

    if(effect){
        //calling adventurerCard failed
        adventurerCardFails++;
    }

    //adventurerCard expected effect
    while(drawntreasure<2){
        if (pre.deckCount[p] <1){//if the deck is empty we need to shuffle discard and add to deck
            sRes = shuffle(p, &pre);

            //check if shuffle failed
            if(sRes == -1 && pre.deckCount[p] >= 1){
                shuffleFails++;
            }
        }
        drawCard(p, &pre);
        cardDrawn = pre.hand[p][pre.handCount[p]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            pre.handCount[p]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        pre.discard[p][pre.discardCount[p]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }

    //counting the treasures
    int i;
    for(i = 0; i < post->handCount[p]; i++){
        treasure = post->hand[p][i];
        if(treasure == copper || treasure == silver || treasure == gold){
            postCoins++;
        }
    }

    for(i = 0; i < pre.handCount[p]; i++){
        treasure = pre.hand[p][i];
        if(treasure == copper || treasure == silver || treasure == gold){
            preCoins++;
        }
    }

    if(postCoins != preCoins){
        drawCardFails++;
    }

    //checking discard pile
    for(i = 0; i < post->discardCount[p]; i++){
        if(post->discard[p][i] == gold){
            goldDiscards++;
        }else if(post->discard[p][i] == silver){
            silverDiscards++;
        }else if(post->discard[p][i] == copper){
            copperDiscards++;
        }
    }

    if(goldDiscards != 0){
        discardFails++;
    }

    if(silverDiscards != 0){
        discardFails++;
    }

    if(copperDiscards != 0){
        discardFails++;
    }

}

int main(){
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int i, n, player;
    int randCard, randK;
    int itr = 200000;
    //int j;
    printf("***RANDOM TEST***\n");
    printf("TESTING adventurerCard...\n");

    //srand(time(NULL));

    SelectStream(2);
    PutSeed(3);
    
    for(i = 0; i < itr; i++){
        //initializing gameState
        initializeGame(2, k, seed, &G);
        // for(j = 0; j < sizeof(struct gameState); j++){
        //     ((char*)&G)[j] = floor(Random() * 256);
        // }
        //printf("trace %d\n", i);
        player = floor(Random() * 2);
        G.deckCount[player] = floor(Random() * (MAX_DECK - 5));
        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * (MAX_HAND - 5));
        G.whoseTurn = player;

        //put random cards in player's deck
        for(n = 0; n < G.deckCount[player]; n++){
            randCard = Random() * 50 + 1;
            randK = Random() * 10;
            if(randCard == 1){
                G.deck[player][n] = copper;
            }else if(randCard == 2){
                G.deck[player][n] = silver;
            }else if(randCard == 3){
                G.deck[player][n] = gold;
            }else{
                G.deck[player][n] = k[randK];
            }
        }
        
        checkAdventurerCard(player, &G);
    }

    int totalFails = adventurerCardFails + drawCardFails + shuffleFails + discardFails;

    if(totalFails == 0){
        printf("ALL RANDOM TESTS PASSED\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
    }else {
        printf("****RESULTS****\n");
        printf("TOTAL ITERATIONS: %d\n", itr);
        printf("adventurerCard call tests fails: %d\n", adventurerCardFails);
        printf("drawCard tests fails: %d\n", drawCardFails);
        printf("shuffle tests fails: %d\n", shuffleFails);
        printf("# of treasure cards discarded fails: %d\n", discardFails);
    }

    return 0;
}