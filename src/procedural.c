#include "valley.h"

void mapProceduralGeneration(Map * map)
{
	mapNoiseGeneration(map, 60); // Generate simple noise on the map with '#' and  ' '
    mapApplyCellularAutomaton(map, 12); // Apply Cellular Automaton a certain number of times
    mapFillWalls(map); // If surrounded by 4 '#', turns into a '.' 
    mapGrassGeneration(map); // Generate randomly grass : ',', '"', '*'

}

void mapGrassGeneration(Map * map)
{
    for(int y = 1; y < map->dimensions.height; y++) 
    {
        for (int x = 1; x < map->dimensions.width; x++)
        {
            int randomNumber = (rand() % 200) + 1; // Create random int between 1 and 200

            if (map->tiles[y][x] == ' ') // If not walls, generate a random grass char
            {   
                if (randomNumber >= 1 && randomNumber <= 10) 
                {
                    map->tiles[y][x] = ',';
                    map->colors[y][x] = 1;
                }
                else if (randomNumber > 10 && randomNumber <= 20) 
                {
                    map->tiles[y][x] = '"';
                    map->colors[y][x] = 1;
                }
                else if (randomNumber > 20 && randomNumber <= 21) 
                {
                    map->tiles[y][x] = '*';
                    map->colors[y][x] = (rand() % 5) + 3; // generate random color
                }
            }
        }   
    }
}


void mapFillWalls(Map * map)
{
    
    Position directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Vectors used to check around the tile

    for(int k = 0; k < map->dimensions.height; k++) 
    {
        for (int j = 0; j < map->dimensions.width; j++)
        {
            int neighbor_wall_count = 0;

            for(int i=0; i<4; i++)
            {   
                
                int new_y = k + directions[i].y; // Check adjacent positions
                int new_x = j + directions[i].x; 
    
                if(new_y < 0 || new_y >= map->dimensions.height || new_x < 0 || new_x >= map->dimensions.width)
                {
                    neighbor_wall_count++;
                }
            else if(map->tiles[new_y][new_x] == '#' || map->tiles[new_y][new_x] == '.') // Count if there is a wall
                {
                    neighbor_wall_count++;
                }  
            }

            
            if (neighbor_wall_count == 4) // If surrounded by walls, palce '.'
            {
                map->tiles[k][j] = '.';
                map->colors[k][j] = 2;
            }
        }   
    }
}

void mapApplyCellularAutomaton(Map * map, int count)
{
    // Basic Cellular Automaton :
    // If there are more than 4 walls around the checked tile, place wall on the checked tile
    // if not, place ground
    for (int i = 0; i < count; i++)
    {
        char ** temp_tiles = copyMap(map); // Copy original map state to use it

        for (int k = 1; k < map->dimensions.height - 1; k++) // Check every tile on the map
        {
            for (int j = 1; j < map->dimensions.width - 1; j++)
            {
                int neighbor_wall_count = 0;
                for (int y = k - 1; y <= k + 1 ; y++)
                {
                    for (int x = j - 1; x <= j + 1; x++)
                    {
                        if (y != k || x != j)
                        {
                            if (temp_tiles[y][x] == '#') // If wall around, count
                            {
                                neighbor_wall_count ++;
                            }
                        }
                    }
                }

                if(neighbor_wall_count > 4)
                {
                    map->tiles[k][j] = '#';
                }
                else
                {
                    map->tiles[k][j] = ' ';
                }
            }
        }
    }
}


void mapNoiseGeneration(Map * map, int density)
{
		
	int chance = 100;

	for (int y = 1 ; y < map->dimensions.height - 1; y++)
	{
		for (int x = 1; x < map->dimensions.width - 1; x++)
		{
			int randomNumber = (rand() % chance) + 1;

			if (randomNumber < density)
			{
				map->tiles[y][x] = '#' ;
			}
		}
	}
}