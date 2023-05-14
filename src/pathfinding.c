#include "valley.h"




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

int isHouseReachable(Game * game, Position house)
{
    // Create an Array containing 'visited' tiles
    char ** visited_tiles = malloc(sizeof(char*) * game->map->dimensions.height);

    for (int y = 0; y < game->map->dimensions.height; y++)
    {
        visited_tiles[y] = malloc(sizeof(char) * game->map->dimensions.width);


        for (int x = 0; x < game->map->dimensions.width; x++)
        {
        visited_tiles[y][x] = '0';
        }
    }

    // Create an array of positions representing tiles which are going to be verified
    int queue_max_size = game->map->dimensions.width * game->map->dimensions.height;
    Position * queue = malloc(sizeof(Position) * queue_max_size);

    int queue_start = 0, queue_end = 0;
        
    // Add the starting point to the queue
    queue[queue_start] = game->player->position;
    queue_start++;

    // Mark the starting point as visited
    visited_tiles[game->player->position.y][game->player->position.x] = '1';

    // Define the four directions: up, down, left, right
    Position directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    while(queue_start != queue_end)
    {
        
        Position current = queue[queue_start]; // Obtain current element in queue
        queue_start++; // Increment the starting queue index


        if (current.y == house.y && current.x == house.x)
        {
            // House is accessible from the player
            return 1;
        }

        for(int i = 0; i < 4; i++)
        {
            // Init neighbor as the tile next to the one already checked for each direction
            Position neighbor;
            neighbor.y = current.y + directions[i].y;
            neighbor.x = current.x + directions[i].x;

            // Check if the neighbor cell is valid and has not been visited yet
            if (neighbor.y >= 0 && neighbor.y < game->map->dimensions.height &&
                neighbor.x >= 0 && neighbor.x < game->map->dimensions.width &&
                visited_tiles[neighbor.y][neighbor.x] == '0' &&
                game->map->tiles[neighbor.y][neighbor.x] != '#')
            {
                // Add the neighbor position to the queue of positions and mark it as visited
                queue[queue_end] = neighbor;
                queue_end++;

                // Mark the tile as visited
                visited_tiles[neighbor.y][neighbor.x] = '1';
            }
        }
    }

    for(int i = 0; i < game->map->dimensions.height; i++)
    {
        free(visited_tiles[i]);
    }
    free(visited_tiles);
    free(queue);

    return 0;
}