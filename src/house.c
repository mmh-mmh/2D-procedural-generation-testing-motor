#include "valley.h"

void placeHouseAtPlayerDistance (Game * game, int distance_limit)
{   
    //Init house position
    Position house;

    // Generate random valid position for the house while till she is reachable not too close the player
    int i = 0;

    do 
    {
        
        generateRandHousePosition(game->map, &house);
        i++;
        if (i > 100)
        {
            return;
        }

    } while (isHouseReachable(game, house) == FALSE /*|| isHouseTooNear(game, house, distance_limit) == TRUE*/); 
}

void generateRandHousePosition (Map * map, Position * house)
{
    do
    {
        house->y = rand() % (map->dimensions.height - 2) + 1;
        house->x = rand() % (map->dimensions.height - 2) + 1;
    } while (map->tiles[house->y][house->x] == '#' || map->tiles[house->y][house->x] == '.');
}