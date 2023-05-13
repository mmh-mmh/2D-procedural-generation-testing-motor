#include "valley.h"


Map * createMap()
{
	Map * map = malloc(sizeof(Map));
	map->dimensions.height = MAP_HEIGHT;
	map->dimensions.width = MAP_WIDTH;

	map->tiles = mapSetup(map);
	mapProceduralGeneration(map);

	return map;
}



char ** mapSetup(Map * map)
{
	char ** tiles;
	tiles = malloc(sizeof(char*) * map->dimensions.height);
	for(int y = 0; y < map->dimensions.height; y++)
	{
		tiles[y] = malloc(sizeof(char) * map->dimensions.width);
	}

	for (int y = 0; y < map->dimensions.height; y++)
	{
		for (int x = 0; x < map->dimensions.width; x++)
		{
			if (y == 0 || y == map->dimensions.height - 1 || x == 0 || x == map->dimensions.width - 1)
			{
				tiles[y][x] = '#';
			}
			else
			{
				tiles[y][x] = ' ';
			}
		}
	}
	return tiles;
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
