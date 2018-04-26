//unit test for shuffle() function

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

int main(){
	int seed = 1000;
	int player = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("TESTING shuffle():\n");

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(2, k, seed, &G);

	G.deckCount[player] = 0;
	printf("Testing with deckCount = 0\n");
	assertTrue(shuffle(player, &G), -1);

	G.deckCount[player] = 20;
	printf("Testing with deckCount = 20\n");
	assertTrue(shuffle(player, &G), 0);

	printf("Testing result of shuffle()\n");
	int before = G.deck[player][0];
	shuffle(player, &G);
	int after = G.deck[player][0];

	if(before == after){
		printf("Test failed\n");
		fail++;
	}else{
		printf("Test successfully completed\n");
	}

	if(fail){
		printf("\n%d tests failed.\n", fail);
	}else {
		printf("\nALL TESTS SUCCESSFULLY COMPLETED\n");
	}

	return 0;
}
