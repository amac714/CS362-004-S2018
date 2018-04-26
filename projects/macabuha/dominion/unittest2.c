//unit test for updateCoins()

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int fail = 0;

void assertTrue(int a, int b) {
	if(a == b){
		printf("TEST SUCCESSFULLY COMPLETED.\n");
	} else {
		printf("TEST FAILED.\n");
		fail++;
	}
}

int main() {
	int seed = 1000;
	int player = 0;
	int bonus, handCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	int i;
	for(i = 0; i < MAX_HAND; i++){
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf("TESTING updateCoinds():\n");

	bonus = 1;
	for(handCount = 1; handCount <= 5; handCount++){
	
		printf("Test with %d treasure card(s) and %d bonus.\n", handCount, bonus);

		memset(&G, 23, sizeof(struct gameState));
		initializeGame(1, k, seed, &G);
		G.handCount[player] = handCount;

		//set all cards to copper
		memcpy(G.hand[player], coppers, sizeof(int) * handCount);
		updateCoins(player, &G, bonus);

		printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
		assertTrue(G.coins, handCount * 1 + bonus); //check if # of coins are correct

		//set all cards to silver
		memcpy(G.hand[player], silvers, sizeof(int) * handCount);
		updateCoins(player, &G, bonus);

		printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
		assertTrue(G.coins, handCount * 2 + bonus); //check if # of coins are correct

		//set all cards to gold
		memcpy(G.hand[player], golds, sizeof(int) * handCount);
		updateCoins(player, &G, bonus);

		printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
		assertTrue(G.coins, handCount * 3 + bonus);

		bonus++;

	}

	if(fail){
		printf("\n%d tests failed\n", fail);
	}else {
		printf("\nALL TESTS SUCCESSFULLY COMPLETED\n");
	}
	
	return 0;
}
