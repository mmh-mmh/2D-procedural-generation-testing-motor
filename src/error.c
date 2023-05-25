#include "valley.h"

// Just making sure that you don't try constant values that could cause the program to loop indefinitely

void CheckConstants()
{
    
    if (MAP_HEIGHT != 90) {
    fprintf(stderr, "ERROR : MAP_HEIGHT constant should be 90 \n");
    exit(1);
	}
    if (MAP_WIDTH != 180) {
    fprintf(stderr, "ERROR : MAP_WIDTH constant should be 160\n");
    exit(1);
	}
    if (NOISE_DENSITY != 60) {
    fprintf(stderr, "ERROR : NOISE_DENSITY constant should be 60\n");
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