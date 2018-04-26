//Unit test for isGameOver function
//game ends if stack of Province cards is empty or 3 supply pile are at 0

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int fail = 0;
int success = 0;

void assertTrue(int a, int b) {
	if(a == b){
		printf("TEST SUCCESSFULLY COMPLETED.\n");
		success++;	
	} else {
		printf("TEST FAILED.\n");
		fail++;
	}
}

int main() {
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int numPlayer = 2;
	int seed = 1000;
	struct gameState G;

	printf("TESTING isGameOver():\n");

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &G);	

	//setting province gameOver condition
	G.supplyCount[province] = 0;

	printf("Testing where province cards = 0:\n");
	assertTrue(isGameOver(&G), 1);

	//resetting province supply count and setting supply pile game over condition
	G.supplyCount[province] = 1;
	
	int i;
	for(i = 0; i < 3; i++){
		G.supplyCount[i] = 0;
	}	

	printf("Testing for 3 empty supply piles...\n");
	assertTrue(isGameOver(&G), 1);

	//resetting supply piles
	for(i = 0; i < 3; i++){
		G.supplyCount[i] = 1;
	}

	printf("Testing for non winning game conditions...\n");
	assertTrue(isGameOver(&G), 0);

	//displaying test results
	if(fail){
		printf("%d tests failed, %d passed.\n", fail, success);
	}else {
		printf("ALL TESTS SUCCESFULLY COMPLETED.\n");
	}

	return 0;
}
