#include "valley.h"

// Classic BFS Pathfinding algorithm used to check if object b is reachable from object a

bool isReachable(Map * map, Position object_a, Position object_b)
{
    // Create an Array containing 'visited' tiles
    unsigned int ** visited_tiles = malloc(sizeof(unsigned int*) * map->dimensions.height);

    for (int y = 0; y < map->dimensions.height; y++)
    {
        visited_tiles[y] = malloc(sizeof(unsigned int) * map->dimensions.width);


        for (int x = 0; x < map->dimensions.width; x++)
        {
        visited_tiles[y][x] = FALSE;
        }
    }

    // Create an array of positions representing tiles which are going to be verified next (queue)
    int queue_max_size = map->dimensions.width * map->dimensions.height;
    Position * queue = malloc(sizeof(Position) * queue_max_size);

    int queue_start = 0, queue_end = 0;
    
    // Add the starting point to the queue
    queue[queue_end] = object_a;
    queue_end++;

    // Mark the starting point as visited
    visited_tiles[object_a.y][object_a.x] = TRUE;

    // Define the four directions: up, down, left, right
    Position directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    while(queue_start != queue_end)
    {
        
        Position current = queue[queue_start]; // Obtain current element in queue
        queue_start++; // Increment the starting queue index


        if (current.y == object_b.y && current.x == object_b.x)
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
            if (neighbor.y >= 0 && neighbor.y < map->dimensions.height &&
                neighbor.x >= 0 && neighbor.x < map->dimensions.width &&
                visited_tiles[neighbor.y][neighbor.x] == FALSE &&
                map->tiles[neighbor.y][neighbor.x] != '#')
            {
                // Add the neighbor position to the queue of positions and mark it as visited
                queue[queue_end] = neighbor;
                queue_end++;

                // Mark the tile as visited
                visited_tiles[neighbor.y][neighbor.x] = TRUE;
            }
        }
    }

    for(int i = 0; i < map->dimensions.height; i++)
    {
        free(visited_tiles[i]);
    }
    free(visited_tiles);
    free(queue);

    // Queue is empty, meaning house is not reachable
    return FALSE;
}