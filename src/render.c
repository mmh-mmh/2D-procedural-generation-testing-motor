#include "valley.h"

void render(Game * game, Windows * windows)
{
    drawMapInGameWindow(game, windows);

	Dimensions main_window_posistion;

	getmaxyx(windows->main_window, main_window_posistion.height, main_window_posistion.width);
	wresize(windows->main_window, main_window_posistion.height, main_window_posistion.width);
	box(windows->main_window, 0, 0);
	wrefresh(windows->main_window);
	refresh();

}


void drawMapInGameWindow(Game * game, Windows * windows)
{
    Dimensions game_window;

    //game_window.height = MAIN_WINDOW_HEIGHT;
    //game_window.width = MAIN_WINDOW_WIDTH;

    getmaxyx(windows->game_window, game_window.height, game_window.width);


	Position mapStartPos;
	mapStartPos.y = game->player->position.y - (game_window.height / 2);
	mapStartPos.x = game->player->position.x - (game_window.width / 2);
	
	Position mapPos;

	int random_color;

	for (int i = 1; i <= game_window.height - 2; i++)
	{
		for (int j = 1; j <= game_window.width - 2; j++)
		{
			mapPos.y = mapStartPos.y + i;
			mapPos.x = mapStartPos.x + j;
			
			if (mapPos.y >= 0 && mapPos.y < game->map->dimensions.height && mapPos.x >= 0 && mapPos.x < game->map->dimensions.width)
			{
				wattron(windows->game_window, COLOR_PAIR(game->map->colors[mapPos.y][mapPos.x]));
                mvwprintw(windows->game_window, i, j, "%c", game->map->tiles[mapPos.y][mapPos.x]);
                wattroff(windows->game_window, COLOR_PAIR(game->map->colors[mapPos.y][mapPos.x]));
			}
			else
			{	
				wattron(windows->game_window, COLOR_PAIR(2));
				mvwprintw(windows->game_window, i, j, ".");
				wattroff(windows->game_window, COLOR_PAIR(2));
			}
		}
	}

	mvwprintw(windows->game_window, game_window.height/2, game_window.width/2, "%c", game->player->skin);

	wresize(windows->game_window, game_window.height, game_window.width);
	box(windows->game_window, 0, 0);
	wrefresh(windows->game_window);
}

