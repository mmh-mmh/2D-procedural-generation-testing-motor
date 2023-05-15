#include "valley.h"

bool isHouseUpLeftCornerReachable(Game * game)
{
    // Create an Array containing 'visited' tiles
    unsigned int ** visited_tiles = malloc(sizeof(unsigned int*) * game->map->dimensions.height);

    for (int y = 0; y < game->map->dimensions.height; y++)
    {
        visited_tiles[y] = malloc(sizeof(unsigned int) * game->map->dimensions.width);


        for (int x = 0; x < game->map->dimensions.width; x++)
        {
        visited_tiles[y][x] = FALSE;
        }
    }

    // Create an array of positions representing tiles which are going to be verified next (queue)
    int queue_max_size = game->map->dimensions.width * game->map->dimensions.height;
    Position * queue = malloc(sizeof(Position) * queue_max_size);

    int queue_start = 0, queue_end = 0;
    
    // Add the starting point to the queue
    queue[queue_end] = game->player->position;
    queue_end++;

    // Mark the starting point as visited
    visited_tiles[game->player->position.y][game->player->position.x] = TRUE;

    // Define the four directions: up, down, left, right
    Position directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    while(queue_start != queue_end)
    {
        
        Position current = queue[queue_start]; // Obtain current element in queue
        queue_start++; // Increment the starting queue index


        if (current.y == game->house->position.y && current.x == game->house->position.x)
        {
            // House is accessible from the player
            return TRUE;
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
                visited_tiles[neighbor.y][neighbor.x] == FALSE &&
                game->map->tiles[neighbor.y][neighbor.x] != '#')
            {
                // Add the neighbor position to the queue of positions and mark it as visited
                queue[queue_end] = neighbor;
                queue_end++;

                // Mark the tile as visited
                visited_tiles[neighbor.y][neighbor.x] = TRUE;
            }
        }
    }

    for(int i = 0; i < game->map->dimensions.height; i++)
    {
        free(visited_tiles[i]);
    }
    free(visited_tiles);
    free(queue);

    return FALSE;
}