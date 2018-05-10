//unit test for great_hall card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "great_hall"

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

	//initialize a game state and player cards
	memset(&G, 23, sizeof(struct gameState));
	memset(&testG, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	//copy game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(great_hall, choice1, choice2, choice3, &testG, handPos, &bonus);

	printf("TEST 1: checking hand count\n");
	assertTrue(testG.handCount[player], G.handCount[player]);	//this should be equal

	printf("TEST 2: checking played card count\n");
	assertTrue(testG.playedCardCount, G.playedCardCount + 1);

	printf("TEST 3: checking actions\n");
	assertTrue(testG.numActions, G.numActions + 1);

	if(fail){
		printf("\n%d tests failed\n", fail);
	}else {
		printf("\nALL TESTS SUCCESSFULLY COMPLETED\n");
	}

	return 0;
}
