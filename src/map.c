#include "valley.h"


Map * mapSetup(int height, int width)
{
	Map * map = malloc(sizeof(Map));
	map->dimensions.height = height;
	map->dimensions.width = width;

	map->tiles = malloc(sizeof(char*) * map->dimensions.height);
	map->colors = malloc(sizeof(int*) * map->dimensions.height);

	for(int y = 0; y < map->dimensions.height; y++)
	{
		map->tiles[y] = malloc(sizeof(char) * map->dimensions.width);
		map->colors[y] = malloc(sizeof(int) * map->dimensions.width);
	}

	return map;
}

void mapGeneration (Game * game)
{
	// Generate proceduraly ground and walls of the map, then try for max_trials to place the player and the structures in the map
    // They must verify certain conditions (not being too near, being reachable...)
    // If max_trials reached, regenerate a map and retry
    int max_trials = 10000;
    do
    {   
        clearMap(game->map); // Sets map to default : empty with # on extremities
        mapProceduralGeneration(game->map); // Proceduraly generate map inside the walls;
    } while ( !TryToPlacePlayerAndStructuresForMaxTrials(game, max_trials));
}

void clearMap(Map * map)
{	
	for (int y = 0; y < map->dimensions.height; y++)
	{
		for (int x = 0; x < map->dimensions.width; x++)
		{
			if (y == 0 || y == map->dimensions.height - 1 || x == 0 || x == map->dimensions.width - 1)
			{
				map->tiles[y][x] = '#';
			}
			else
			{
				map->tiles[y][x] = ' ';
			}
			
			map->colors[y][x] = WHITE_ON_DEFAULT;
		}
	}
}

void SaveMapTilesAndColors(Map * map)
{
	map->tiles_save = copyCharArrayOfArray(map->tiles, map->dimensions);
	map->colors_save = copyIntArrayOfArray(map->colors, map->dimensions);
}