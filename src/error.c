#include "valley.h"


void CheckConstants()
{
    if (MAP_HEIGHT < 80) {
    fprintf(stderr, "ERROR : MAP_HEIGHT is too low (< 80) \n");
    exit(1);
	}
    if (MAP_WIDTH < 160) {
    fprintf(stderr, "ERROR : MAP_WIDTH constant is too low (< 160)\n");
    exit(1);
	}
    if (NOISE_DENSITY != 60) {
    fprintf(stderr, "ERROR : NOISE_DENSITY constant should be 60\n");
    exit(1);
    }
    if (CELLULAR_AUTOMATON_ITERATIONS != 12) {
    fprintf(stderr, "ERROR : CELLULAR_AUTOMATON_ITERATIONS constant should be 12\n");
    exit(1);
    }
    if (HOUSE_SIZE < 6) {
    fprintf(stderr, "ERROR : HOUSE_SIZE constant is too low (< 6)\n");
    exit(1);
	}
    if (HOUSE_MINIMAL_DISTANCE > MAP_HEIGHT - (HOUSE_SIZE + 10) || HOUSE_MINIMAL_DISTANCE > MAP_WIDTH - (HOUSE_SIZE + 10)) {
    fprintf(stderr, "ERROR : HOUSE_MINIMAL_DISTANCE is too long\n");
    exit(1);
	}
}