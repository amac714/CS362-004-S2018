//unit test for drawCard() function

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int fail = 0;

void assertTrue(int a, int b){
	if(a == b){
		printf("Test successfully completed\n");
	} else {
		printf("Test failed\n");
		fail++;
	}
}

int main() {
	int seed = 1000;
	int player = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("TESTING drawCard():\n");

	//initialize game
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(2, k, seed, &G);

	//empty deck
	G.deckCount[player] = 0;
	G.discardCount[player] = 5;
	//hand count
	G.handCount[player] = 1;

	int currHand = G.handCount[player];
	drawCard(player, &G);
	
	printf("Current handCount = %d, expected = %d\n", G.handCount[player], currHand + 1);
	assertTrue(G.handCount[player], currHand + 1);

	printf("Current deckCount = %d, expected = 4\n", G.deckCount[player]);
	assertTrue(G.deckCount[player], 4);

	//testing drawCard with non-empty deck (4)
	drawCard(player, &G);	
	printf("Current handCount = %d, expected = 3\n", G.handCount[player]);
	assertTrue(G.handCount[player], 3);

	printf("Current deckCount = %d, expected = 3\n", G.deckCount[player]);
	assertTrue(G.deckCount[player], 3);

	if(fail){
		printf("\n%d tests failed.\n", fail);
	}else {
		printf("\nALL TESTS SUCCESSFULLY COMPLETED\n");
	}

	return 0;
}
