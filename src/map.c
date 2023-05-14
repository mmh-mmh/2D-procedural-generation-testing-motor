#include "valley.h"


Map * createMap()
{
	Map * map = malloc(sizeof(Map));
	map->dimensions.height = MAP_HEIGHT;
	map->dimensions.width = MAP_WIDTH;

	mapSetup(map);
	mapProceduralGeneration(map);

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
    int trials, maxTrials = 1000;
	int houseMinDistance = 20;

	do
	{
	trials = 0;
    setRandomSpawn(game);
    placeHouseAtPlayerDistance(game, houseMinDistance, &trials, &maxTrials);
	} while (trials >= maxTrials);
}