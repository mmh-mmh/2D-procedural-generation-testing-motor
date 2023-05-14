#include "valley.h"

void placeHouseAtPlayerDistance (Game * game, int distance_limit, int * trials, int * max_trials)
{   
    do // Generate a random valid position for the house while till she is reachable and not too close the player
    {
    generateRandHousePosition(game);
    (*trials)++;
        if (*trials >= *max_trials) // If trials reaches maxTrials, return to create another map
        {
            return;
        }
    } while (isHouseReachable(game) == FALSE || isHouseTooNear(game, distance_limit) == TRUE); 

    game->map->tiles[game->house->position.y][game->house->position.x] = 'H';
    game->map->colors[game->house->position.y][game->house->position.x] = 3;
}

 void generateHouse()
{
    return;
}

void generateRandHousePosition (Game * game)
{
    do
    {
        game->house->position.y = (rand() % (game->map->dimensions.height - 2)) + 1;
        game->house->position.x = (rand() % (game->map->dimensions.width - 2)) + 1;
    } while (game->map->tiles[game->house->position.y][game->house->position.x] == '#' || game->map->tiles[game->house->position.y][game->house->position.x] == '.');
}

int isHouseTooNear(Game * game, int distance_limit)
{   
    double dx = game->house->position.x - game->player->position.x;
    double dy = game->house->position.y - game->player->position.y;
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