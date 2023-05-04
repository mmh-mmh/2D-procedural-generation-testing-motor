#include "valley.h"

char ** mapSetup(int height, int width)
{	
	char ** map;
	map = malloc(sizeof(char*) * height);
	for(int y = 0; y < height; y++)
	{
		map[y] = malloc(sizeof(char*) * width);
		
	}
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y == 0 || y == height-1 || x == 0 || x == width-1)
			{
				map[y][x] = '#';
			}
			else
			{
				map[y][x] = ' ';
			}
		}
	}
	return map;
}

int mapNotMovableGeneration(Level * level)
{
	mapRandGrassGeneration(level->map);
	mapRandRockGeneration(level->map);
	mapRandHouseGeneration(level);

	return 0;
}


int drawMapInGameWindow(WINDOW * gameWindow, char ** map, PlayerStruct * player)
{
	Position mapStartPos;
	mapStartPos.y = player->position.y - (GAME_WINDOW_HEIGHT / 2);
	mapStartPos.x = player->position.x - (GAME_WINDOW_WIDTH / 2);
	
	Position mapPos;

	start_color();
	use_default_colors();
	init_pair(1, COLOR_GREEN, -1);

	for (int i = 1; i <= GAME_WINDOW_HEIGHT - 2; i++)
	{
		for (int j = 1; j <= GAME_WINDOW_WIDTH - 2; j++)
		{
			mapPos.y = mapStartPos.y + i;
			mapPos.x = mapStartPos.x + j;
			
			if (mapPos.y >= 0 && mapPos.y < MAP_HEIGHT && mapPos.x >= 0 && mapPos.x < MAP_WIDTH)
			{	
				if(map[mapPos.y][mapPos.x] == ',' || map[mapPos.y][mapPos.x] == '"')
				{
				wattron(gameWindow, COLOR_PAIR(1));
				mvwprintw(gameWindow, i, j, "%c", map[mapPos.y][mapPos.x]);
				wattroff(gameWindow, COLOR_PAIR(1));
				}
				else
				{
					mvwprintw(gameWindow, i, j, "%c", map[mapPos.y][mapPos.x]);
				}
			}
			else
			{
				mvwprintw(gameWindow, i, j, " ");
			}
		}
	}

	mvwprintw(gameWindow, GAME_WINDOW_HEIGHT/2, GAME_WINDOW_WIDTH/2, "%c", player->skin);

	wresize(gameWindow, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
	box(gameWindow, 0, 0);
	wrefresh(gameWindow);
	
	return 0;
}



int mapRandGrassGeneration(char ** map)
{
	
	int proba1 = 8;
	int proba2 = 16;
	int chance = 100;

	for (int y = 1 ; y < MAP_HEIGHT - 1; y++)
	{
		for (int x = 1; x < MAP_WIDTH - 1; x++)
		{
			int randomNumber = rand() % chance;

			if (randomNumber < proba1)
			{
				map[y][x] = ',' ;
			}

			else if (randomNumber < proba2)
			{
				map[y][x] = '"';
			}
		}
	}

	return 0;
}

int mapRandRockGeneration(char ** map)
{

	int proba = 1;
	int chance = 300;
	
	for (int y = 1 ; y < MAP_HEIGHT; y++)
	{
		for (int x = 1; x < MAP_WIDTH; x++)
		{
			
			if (rand() % chance < proba)
			{
				map[y][x] = '&';
			}
		}
	}
	return 0;	
} 

int mapRandHouseGeneration(Level * level)
{
	int houseHeight = HOUSE_SIZE;
	int houseWidth = HOUSE_SIZE*2;
	int houseY = (rand() % (MAP_HEIGHT - (houseHeight + 3))) + 2;
	int houseX = (rand() % (MAP_WIDTH - (houseWidth + 3))) + 2;

	//level->HousePosition.y = houseY;
	//level->HousePosition.x = houseX;

	Position doorPos;
	
	switch (rand()%4)
	{
		case 0:
			doorPos.x = houseX + houseWidth/2;
			doorPos.y = houseY;
			break;
		case 1:
			doorPos.x = houseX + houseWidth/2;
			doorPos.y = houseY + houseHeight-1;
			break;
		case 2:
			doorPos.x = houseX;
			doorPos.y = houseY + houseHeight/2;
			break;
		case 3:
			doorPos.x = houseX + houseWidth-1;
			doorPos.y = houseY + houseHeight/2;
			break;
	}
	
	for (int y = houseY; y < houseY + houseHeight; y++)
	{
		for(int x = houseX; x < houseX + houseWidth; x++)
		{
			if(x == doorPos.x && y == doorPos.y)
			{
				level->map[y][x] = ' ';
				unblockDoor(level->map, &doorPos);
			}
			else if (y == houseY || y == houseY + houseHeight - 1 || x == houseX || x == houseX + houseWidth - 1)
			{
				level->map[y][x] = '#';
			}
			else
			{
				level->map[y][x] = ' ';
			}
		}
	}

	return 0;
}

int unblockDoor(char ** map, Position * doorPos)
{
	for(int y = (doorPos->y - 1); y <= (doorPos->y + 1); y++)
	{
		for(int x = (doorPos->x - 1); x <= (doorPos->x + 1); x++)
		{
			if(map[y][x] == '&')
			{
				map[y][x] = ' ';
			}
		}
	}

	return 0;
}

int mapMovableGeneration(char ** map)
{
	int y, x;

	do
	{
		y = (rand() % (MAP_HEIGHT - 4) ) + 2;
		x = (rand() % (MAP_WIDTH - 4) ) + 2;
	} while (map[y][x] == '#');

	map[y][x] = 'O';

	return 0;
}

char ** saveMap(char ** map)
{
	char ** mapSave;
	mapSave = malloc(sizeof(char*) * MAP_HEIGHT);

	for(int y = 0; y < MAP_HEIGHT; y++)
	{
		mapSave[y] = malloc(sizeof(char*) * MAP_WIDTH);

		for(int x = 0; x < MAP_WIDTH; x++)
		{
			mapSave[y][x] = map[y][x];
		}
	}

	return mapSave;
}