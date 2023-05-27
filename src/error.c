#include "valley.h"

// Just making sure that you don't try constant values that could cause the program to loop indefinitely

void CheckConstants()
{
    
    if (MAP_HEIGHT <= 80) {
    fprintf(stderr, "ERROR : MAP_HEIGHT constant is too low (< 80) \n");
    exit(1);
	}
    if (MAP_WIDTH <= 160) {
    fprintf(stderr, "ERROR : MAP_WIDTH constant is too low (< 160)\n");
    exit(1);
	}
    if (NOISE_DENSITY >= 65) {
    fprintf(stderr, "ERROR : NOISE_DENSITY constant is too high (>= 65)\n");
    exit(1);
    }
    if (CELLULAR_AUTOMATON_ITERATIONS != 13) {
    fprintf(stderr, "ERROR : CELLULAR_AUTOMATON_ITERATIONS constant should be 13\n");
    exit(1);
    }
    if (HOUSE_SIZE < 6) {
    fprintf(stderr, "ERROR : HOUSE_SIZE constant is too low (< 6)\n");
    exit(1);
	}
    if (HOUSE_MINIMAL_DISTANCE_FROM_PLAYER > MAP_HEIGHT - (HOUSE_SIZE + 10) || HOUSE_MINIMAL_DISTANCE_FROM_PLAYER > MAP_WIDTH - (HOUSE_SIZE + 10)) {
    fprintf(stderr, "ERROR : HOUSE_MINIMAL_DISTANCE_FROM_PLAYER is too long\n");
    exit(1);
	}
    if (DUNGEON_MINIMAL_DISTANCE_FROM_PLAYER > MAP_HEIGHT - (HOUSE_SIZE + 10) || DUNGEON_MINIMAL_DISTANCE_FROM_PLAYER > MAP_WIDTH - (HOUSE_SIZE + 10)) {
    fprintf(stderr, "ERROR : DUNGEON_MINIMAL_DISTANCE_FROM_PLAYER is too long\n");
    exit(1);
	}
}