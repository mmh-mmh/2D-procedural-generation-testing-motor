#include "valley.h"

void placeHouseAtPlayerDistance (Game * game, int distance_limit, int * trials, int * maxTrials)
{   
    Position house;
    
    do // Generate a random valid position for the house while till she is reachable and not too close the player
    {
    generateRandHousePosition(game->map, &house);
    (*trials)++;
        if (*trials >= *maxTrials) // If trials reaches maxTrials, return to create another map
        {
            return;
        }
    } while (isHouseReachable(game, house) == FALSE || isHouseTooNear(game, house, distance_limit) == TRUE); 

    game->map->tiles[house.y][house.x] = 'H';
    game->map->colors[house.y][house.x] = 3;
}

void generateRandHousePosition (Map * map, Position * house)
{
    do
    {
        house->y = (rand() % (map->dimensions.height - 2)) + 1;
        house->x = (rand() % (map->dimensions.width - 2)) + 1;
    } while (map->tiles[house->y][house->x] == '#' || map->tiles[house->y][house->x] == '.');
}

int isHouseTooNear(Game * game, Position house, int distance_limit)
{   
    double dx = house.x - game->player->position.x;
    double dy = house.y - game->player->position.y;
    double housePlayerDistance = sqrt(dx * dx + dy * dy);

    if (housePlayerDistance < distance_limit)
    {
        return 1; // House is too near
    }
    else
    {
        return 0; // House is not too near
    }
}