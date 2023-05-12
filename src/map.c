#include "valley.h"

char ** mapSetup(int height, int width, Level * level)
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
			if (y == 0 || y == height-1 || x == 0 || x == width - 1)
			{
				map[y][x] = '#';
			}
			else
			{
				map[y][x] = ' ';
			}
		}
	}
}

int mapGeneration(Level * level)
{
	
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

int houseGeneration(Level * level)
{

	int houseHeight = HOUSE_SIZE;
	int houseWidth = HOUSE_SIZE*2;
	int houseY = (rand() % (MAP_HEIGHT - (houseHeight + 3))) + 2;
	int houseX = (rand() % (MAP_WIDTH - (houseWidth + 3))) + 2;


	for (int y = houseY; y < houseY + houseHeight; y++)
	{
		for(int x = houseX; x < houseX + houseWidth; x++)
		{
			if( ((y > houseY) && y < (houseY + houseHeight - 1)) && ((x > houseX) && x < (houseX + houseWidth - 1)) )
			{
				level->map[y][x] = ' ';
			}
			else
			{
				level->map[y][x] = '#';
			}
		}
	}

	return 0;
}
