#include "valley.h"

void render(Game * game, WINDOW * main_window)
{
    drawMapInGameWindow(game, main_window);
}


void drawMapInGameWindow(Game * game, WINDOW * gameWindow)
{
    Dimensions game_window;

    game_window.height = MAIN_WINDOW_HEIGHT;
    game_window.width = MAIN_WINDOW_WIDTH;

    //getmaxyx(gameWindow, game_window.height, game_window.width);


	Position mapStartPos;
	mapStartPos.y = game->player->position.y - (game_window.height / 2);
	mapStartPos.x = game->player->position.x - (game_window.width / 2);
	
	Position mapPos;

	for (int i = 1; i <= game_window.height - 2; i++)
	{
		for (int j = 1; j <= game_window.width - 2; j++)
		{
			mapPos.y = mapStartPos.y + i;
			mapPos.x = mapStartPos.x + j;
			
			if (mapPos.y >= 0 && mapPos.y < game->map->dimensions.height && mapPos.x >= 0 && mapPos.x < game->map->dimensions.width)
			{	
				mvwprintw(gameWindow, i, j, "%c", game->map->tiles[mapPos.y][mapPos.x]);
			}
			else
			{
				mvwprintw(gameWindow, i, j, " ");
			}
		}
	}

	mvwprintw(gameWindow, game_window.height/2, game_window.width/2, "%c", game->player->skin);

	wresize(gameWindow, game_window.height, game_window.width);
	box(gameWindow, 0, 0);
	wrefresh(gameWindow);
}

