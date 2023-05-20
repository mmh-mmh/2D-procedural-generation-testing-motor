#include "valley.h"


Map * mapSetup(int height, int width)
{
	Map * map = malloc(sizeof(Map));
	map->dimensions.height = height;
	map->dimensions.width = width;

	char ** tiles;
	map->tiles = malloc(sizeof(char*) * map->dimensions.height);
	map->colors = malloc(sizeof(int*) * map->dimensions.height);

	for(int y = 0; y < map->dimensions.height; y++)
	{
		map->tiles[y] = malloc(sizeof(char) * map->dimensions.width);
		map->colors[y] = malloc(sizeof(int) * map->dimensions.width);
	}

	return map;
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


char ** copyMap(Map * map)
{
	char ** tiles_save = malloc(map->dimensions.height * sizeof(char *));

	for (int y = 0; y < map->dimensions.height; y++)
	{
		tiles_save[y] = malloc(map->dimensions.width * sizeof(char));

		for (int x = 0; x < map->dimensions.width; x++)
		{
				tiles_save[y][x] = map->tiles[y][x];
		}
	}
	return tiles_save;
}