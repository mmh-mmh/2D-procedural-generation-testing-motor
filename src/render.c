#include "valley.h"

void render(Game * game, Windows * windows)
{
    drawMapInGameWindow(game, windows); // As it says

	Dimensions main_window_posistion;

	// Gesture of ncurses's windows display refresh
	getmaxyx(windows->main_window, main_window_posistion.height, main_window_posistion.width); // Get Dimensions of a window
	wresize(windows->main_window, main_window_posistion.height, main_window_posistion.width); // Resolves certain display bugs
	box(windows->main_window, 0, 0); // 'Box' the window : had white outlines
	wrefresh(windows->main_window); // refresh the main window

}


void drawMapInGameWindow(Game * game, Windows * windows)
{
    Dimensions game_window;

    //game_window.height = MAIN_WINDOW_HEIGHT;
    //game_window.width = MAIN_WINDOW_WIDTH;

    getmaxyx(windows->game_window, game_window.height, game_window.width); // Get the game display window dimensions


	Position start_printing_position;

	// Deduct where to start printing inside of the game Window
	// That's basically the top left corner inside the window
	// Considering the middle of the window is the player position
	start_printing_position.y = game->player->position.y - (game_window.height / 2);  
	start_printing_position.x = game->player->position.x - (game_window.width / 2);
	
	Position printing_position;

	for (int i = 1; i <= game_window.height - 2; i++) // Print the game in the limits of the window
	{
		for (int j = 1; j <= game_window.width - 2; j++)
		{
			printing_position.y = start_printing_position.y + i; // Iterate throught the map
			printing_position.x = start_printing_position.x + j;
			
			if (printing_position.y >= 0 && printing_position.y < game->map->dimensions.height && printing_position.x >= 0 && printing_position.x < game->map->dimensions.width)
			{

				// Makes the link between where it is inside the window, and where it is on the map
				// Remembering the printing position DEPENDS of the player position, wich is the center of the window,
				// it will keep the player in the center, and actualise its surroundings

				wattron(windows->game_window, COLOR_PAIR(game->map->colors[printing_position.y][printing_position.x]));
                mvwprintw(windows->game_window, i, j, "%c", game->map->tiles[printing_position.y][printing_position.x]);
                wattroff(windows->game_window, COLOR_PAIR(game->map->colors[printing_position.y][printing_position.x]));
			}
			else // If it is outside of the map, print '.', so we can print infitely '.' for out of bounds without having to stock it
			{	
				wattron(windows->game_window, COLOR_PAIR(2));
				mvwprintw(windows->game_window, i, j, ".");
				wattroff(windows->game_window, COLOR_PAIR(2));
			}
		}
	}

	// Finally puts the player skin at its position, the middle of the window
	mvwprintw(windows->game_window, game_window.height/2, game_window.width/2, "%c", game->player->skin);

	wresize(windows->game_window, game_window.height, game_window.width); // Avoids bugs
	box(windows->game_window, 0, 0); // add white outlines
	wrefresh(windows->game_window); //actualise the window
}

