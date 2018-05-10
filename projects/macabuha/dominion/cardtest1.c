//unit test for adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "adventurer"

int fail = 0;

void assertTrue(int a, int b){
	if(a == b){
		printf("Test successfully completed\n");
	} else {
		printf("Test failed\n");
		fail++;
	}
}

int main(){
	int seed = 1000;
	int player = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int testTreasureCount = 0, treasureCount = 0;
	int card, testCard;

	//initialize a game state and player cards
	memset(&G, 23, sizeof(struct gameState));
	memset(&testG, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	//copy game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	printf("TEST 1: checking treasure cards\n");
	
	int i;
	for(i = 0; i < testG.handCount[player]; i++){
		testCard = testG.hand[player][i];
		if(testCard == copper || testCard == silver || testCard == gold){
			testTreasureCount++;
		}
	}

	for(i = 0; i < G.handCount[player]; i++){
		card = G.hand[player][i];
		if(card == copper || card == silver || card == gold){
			treasureCount++;
		}
	}

	assertTrue(treasureCount+2, testTreasureCount);

	printf("TEST 2: checking hand count\n");
	assertTrue(testG.handCount[player], G.handCount[player]+2);	
	
	if(fail){
		printf("\n%d test(s) failed\n", fail);
	}else {
		printf("\nALL TESTS SUCCESSFULLY COMPLETED\n");
	}

	return 0;
}
