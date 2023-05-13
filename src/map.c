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



void mapProceduralGeneration(Map * map)
{
		
	int proba1 = 8;
	int proba2 = 0;
	int chance = 100;

	for (int y = 1 ; y < map->dimensions.height - 1; y++)
	{
		for (int x = 1; x < map->dimensions.width - 1; x++)
		{
			int randomNumber = rand() % chance;

			if (randomNumber < proba1)
			{
				map->tiles[y][x] = ',' ;
			}

			else if (randomNumber < proba2)
			{
				map->tiles[y][x] = '"';
			}
		}
	}
}