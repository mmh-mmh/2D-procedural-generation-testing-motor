#include "valley.h"

void mapProceduralGeneration(Map * map)
{
	mapNoiseGeneration(map, 60);
    mapApplyCellularAutomaton(map, 11);
    mapFillWalls(map);
}


void mapFillWalls(Map * map)
{
    for(int k = 1; k < map->dimensions.height - 1; k++) 
    {
        for (int j = 1; j < map->dimensions.width - 1; j++)
        {
            int y,x; 
            int neighbor_wall_count = 0;

            for (y = k - 1; y <= k + 1 ; y++)
            {
                if (y != k)
                {
                    if (map->tiles[y][j] == '#' || map->tiles[y][j] == '.')
                    {
                        neighbor_wall_count ++;
                    }
                }
                
            }

            for (x = j - 1; x <= j + 1 ; x++)
            {
                if (x != j)
                {
                    if (map->tiles[k][x] == '#' || map->tiles[k][x] == '.')
                    {
                        neighbor_wall_count ++;
                    }
                }
                
            }

            if (neighbor_wall_count == 4)
            {
                map->tiles[k][j] = '.';
            }
        }   
    }
}

void mapApplyCellularAutomaton(Map * map, int count)
{
    for (int i = 0; i < count; i++)
    {
        char ** temp_tiles = copyMap(map);
        for (int k = 1; k < map->dimensions.height - 1; k++)
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
                            if (temp_tiles[y][x] == '#')
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
		
	int proba = density;
	int chance = 100;

	for (int y = 1 ; y < map->dimensions.height - 1; y++)
	{
		for (int x = 1; x < map->dimensions.width - 1; x++)
		{
			int randomNumber = (rand() % chance) + 1;

			if (randomNumber < proba)
			{
				map->tiles[y][x] = '#' ;
			}
		}
	}
}