#include "valley.h"


Map * createMap()
{
	Map * map = malloc(sizeof(Map));
	map->dimensions.height = MAP_HEIGHT;
	map->dimensions.width = MAP_WIDTH;

	mapSetup(map); // Malloc map and colors and place walls at map extremities
	mapProceduralGeneration(map); // Proceduraly generate map inside the walls

	return map;
}

void mapSetup(Map * map)
{	
	char ** tiles;
	map->tiles = malloc(sizeof(char*) * map->dimensions.height);
	map->colors = malloc(sizeof(int*) * map->dimensions.height);

	for(int y = 0; y < map->dimensions.height; y++)
	{
		map->tiles[y] = malloc(sizeof(char) * map->dimensions.width);
		map->colors[y] = malloc(sizeof(int) * map->dimensions.width);
	}
	
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
			
			map->colors[y][x] = 2;
		}
	}
}


char ** copyMap(Map * map)
{
	char ** temp_tiles = malloc(map->dimensions.height * sizeof(char *));

	for (int y = 0; y < map->dimensions.height; y++)
	{
		temp_tiles[y] = malloc(map->dimensions.width * sizeof(char));

		for (int x = 0; x < map->dimensions.width; x++)
		{
				temp_tiles[y][x] = map->tiles[y][x];
		}
	}
	return temp_tiles;
}


void placePlayerAndStructures(Game * game)
{
	game->house = malloc(sizeof(House));

	int house_minimal_distance = HOUSE_MINIMAL_DISTANCE; // Minimal distance between the player and the house for the generatinon to be correct

	int trials, max_trials = 20000; // Max trials of placing the house before generating another map
	// the number is chosen to be not to high, not wasting time trying to generate house in an invalid map
	// and to be not to low, allowing the srand(time(NULL)) seed to have the time to change before generating
	// another map and not wasting time testing two times the same invalid map

	do
	{
	printw("1MapTried "); // Temporary indicator of how many maps are being generated before finding one valid
	trials = 0;

	//srand(time(NULL));
	setRandomSpawn(game); // Set a random valid spawn point for the player
    placeHouseAtPlayerDistance(game, house_minimal_distance, &trials, &max_trials); // Try to place house until conditions are valid or the max trials have been reached
	} while (trials >= max_trials); // Loop if the map is invalid, creating another map
}