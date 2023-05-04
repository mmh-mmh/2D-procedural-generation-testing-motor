#include "valley.h"

Level * createLevel()
{
    Level * newLevel = malloc(sizeof(Level*));

    newLevel->player = playerSetup(PLAYER_START_POSITION_Y, PLAYER_START_POSITION_X); 

    newLevel->map = mapSetup(MAP_HEIGHT, MAP_WIDTH);

	mapNotMovableGeneration(newLevel);

	newLevel->mapSave = saveMap(newLevel->map);

	mapMovableGeneration(newLevel->map);

    return newLevel;
}