#include "valley.h"

void mapProceduralGeneration(Map * map)
{
	mapNoiseGeneration(map, 60);
    mapApplyCellularAutomaton(map, 12);
    mapFillWalls(map);
    mapGrassGeneration(map);

}

void mapGrassGeneration(Map * map)
{
    for(int y = 1; y < map->dimensions.height; y++) 
    {
        for (int x = 1; x < map->dimensions.width; x++)
        {
            int randomNumber = (rand() % 200) + 1;

            if (map->tiles[y][x] == ' ')
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
                    map->colors[y][x] = (rand() % 5) + 3;
                }
            }
        }   
    }
}


void mapFillWalls(Map * map)
{
    for(int k = 0; k < map->dimensions.height; k++) 
    {
        for (int j = 0; j < map->dimensions.width; j++)
        {
            int y,x; 
            int neighbor_wall_count = 0;

            for (y = k - 1; y <= k + 1 ; y++)
            {
                if (y != k)
                {
                    if (y < 0 || y >= map->dimensions.height || y == k)
                    {
                        neighbor_wall_count ++;
                    }
                    else if (map->tiles[y][j] == '#' || map->tiles[y][j] == '.')
                    {
                        neighbor_wall_count ++;
                    }
                }
            }

            for (x = j - 1; x <= j + 1 ; x++)
            {
                if (x != j)
                {
                    if (x < 0 || x >= map->dimensions.width || x == j)
                    {
                        neighbor_wall_count ++;
                    }
                    else if (map->tiles[k][x] == '#' || map->tiles[k][x] == '.')
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