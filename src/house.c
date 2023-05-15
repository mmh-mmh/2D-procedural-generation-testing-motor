#include "valley.h"

void placeHouseAtPlayerDistance (Game * game, int distance_limit, int * trials, int * max_trials)
{   
    generateRandomHouseDimensionsBetweenTwoNumbers (game->house, 5, 7);


    do // Generate a random valid position for the house while till she is reachable and not too close the player
    {
    generateRandomHousePosition(game);
    (*trials)++;
        if (*trials >= *max_trials) // If trials reaches maxTrials, return to create another map
        {
            return;
        }
    } while (isHouseReachable(game) == FALSE || isHouseTooNear(game, distance_limit) == TRUE); 


    generateHouse(game);
}

bool isHouseReachable(Game * game)
{
    if (isHouseUpLeftCornerReachable(game) == TRUE && isHouseStuck(game) == FALSE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool isHouseStuck(Game * game)
{
    Position pos = game->house->position;
    Dimensions dim = game->house->dimensions;

    for(int y = pos.y - 1; y < pos.y + dim.height + 1; y++)
    {
        for(int x = pos.x - 1; x < pos.x + dim.width + 1; x++)
        {
            if(game->map->tiles[y][x] == '#')
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}


 void generateHouse(Game * game)
{
    Position pos = game->house->position;
    Dimensions dim = game->house->dimensions;

    for(int y = pos.y; y < pos.y + dim.height; y++)
    {
        for(int x = pos.x; x < pos.x + dim.width; x++)
        {
            if(y == pos.y || y == pos.y + dim.height - 1 || x == pos.x || x == pos.x + dim.width - 1)
            {
                game->map->tiles[y][x] = '#';
                game->map->colors[y][x] = 2;
            }
            else
            {
                game->map->tiles[y][x] = ' ';
                game->map->colors[y][x] = 2;
            }
        }
    }

	switch (rand()%4)
	{
		case 0:
			game->house->door_position.x = pos.x + dim.width/2;
			game->house->door_position.y = pos.y;
			break;
		case 1:
			game->house->door_position.x = pos.x + dim.width/2;
			game->house->door_position.y = pos.y + dim.height-1;
			break;
		case 2:
			game->house->door_position.x = pos.x;
			game->house->door_position.y = pos.y + dim.height/2;
			break;
		case 3:
			game->house->door_position.x = pos.x + dim.width-1;
			game->house->door_position.y = pos.y + dim.height/2;
			break;
	}
    
    game->map->tiles[game->house->door_position.y][game->house->door_position.x] = ' ';
    game->map->colors[game->house->door_position.y][game->house->door_position.x] = 2;

}

void generateRandomHouseDimensionsBetweenTwoNumbers (House * house, int num1, int num2)
{
    if (num2 < num1)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    house->dimensions.height = (rand() % (num2 - num1)) + 1 + num1;
    house->dimensions.width = 2*house->dimensions.height;
}



void generateRandomHousePosition (Game * game)
{
    do
    {
        game->house->position.y = (rand() % (game->map->dimensions.height - (game->house->dimensions.height + 4))) + 2;
        game->house->position.x = (rand() % (game->map->dimensions.width - (game->house->dimensions.width + 4))) + 2;
    } while (game->map->tiles[game->house->position.y][game->house->position.x] == '#' || game->map->tiles[game->house->position.y][game->house->position.x] == '.');
}

bool isHouseTooNear (Game * game, int distance_limit)
{   
    double dx = game->house->position.x - game->player->position.x;
    double dy = game->house->position.y - game->player->position.y;
    double housePlayerDistance = sqrt(dx * dx + dy * dy);

    if (housePlayerDistance < distance_limit)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}