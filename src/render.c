#include "valley.h"

void render(Game * game, Windows * windows)
{
	//Changes are stored in the buffer, then applied at ther same time with refreshWindows()

    printMapInWindow(game, windows); // As it says
	printInventoryInWindow(game->player, windows->inventory_window); // Seeks player's inventory informations to print them in the inventory window
	printStatsInWindow(game, windows->stats_window); // Seeks player's stats informations to print them in the inventory window


	refreshWindows(windows); // Gesture of ncurses's windows display refresh / refresh all windows 
}

void printStatsInWindow (Game * game, WINDOW * stats_window)
{	
	mvwprintw(stats_window, 2, 3, "[%d,%d]", game->player->position.y, game->player->position.x);

	mvwprintw(stats_window, 4, 3, "HP   %d/%d", game->player->health, game->player->max_health);

	if(game->player->inventory[0] != NULL)
	{
		mvwprintw(stats_window, 5, 3, "ATK  %d + %d", game->player->base_attack , (*game->player->inventory)->mainItems.weapon->damage);
	}
	else
	{
		mvwprintw(stats_window, 5, 3, "ATK  %d", game->player->base_attack);
	}

	// Get the current time
    time_t current_time = time(NULL);
    
    // Calculate elapsed time
    int elapsed_time = difftime(current_time, game->start_time);
    
    // Convert elapsed time to minutes and seconds
    int minutes = elapsed_time / 60;
    int seconds = elapsed_time % 60;

    // Print the elapsed time
    mvwprintw(stats_window, 7, 3, "Time : %02d:%02d", minutes, seconds);

	mvwprintw(stats_window, 9, 3, "Score : %d", game->player->score);

	return;
}

void printInventoryInWindow (PlayerStruct * player, WINDOW * inventory_window)
{
	mvwprintw(inventory_window, 1, 3,"INVENTORY");
	for(int i = 0; i < player->inventory_size; i++)
	{
		if(player->inventory[i] != NULL)
		{
			mvwprintw(inventory_window, (i+3), 3,"%d - %s", (i+1), player->inventory[i]->name);
		}
		else
		{
			mvwprintw(inventory_window, (i+3), 3, "%d - Empty        ", (i + 1));
		}
	}

	return;
}


void refreshWindows(Windows * windows)
{
	// getmaxyx(windows->main_window, main_window_position.height, main_window_position.width); // Get Dimensions of a window

	wresize(windows->main_window, windows->main_dimensions.height, windows->main_dimensions.width); // Resizes the window, fixes some display bugs
	
	wresize(windows->game_window, (0.75)*windows->main_dimensions.height, (0.80)*windows->main_dimensions.width);
	box(windows->game_window, 0, 0); // 'Box' the window : had white outlines
	wnoutrefresh(windows->game_window); // This function is used to refresh a window in the buffer but not on the screen.
	
	wresize(windows->text_window, (0.25)*windows->main_dimensions.height, (0.80)*windows->main_dimensions.width);
	box(windows->text_window, 0, 0);
	wnoutrefresh(windows->text_window);

	wresize(windows->stats_window, (0.5)*windows->main_dimensions.height, (0.20)*windows->main_dimensions.width);
	box(windows->stats_window, 0, 0);
	wnoutrefresh(windows->stats_window);

	wresize(windows->inventory_window, ((0.5)*windows->main_dimensions.height), (0.20)*windows->main_dimensions.width);
	box(windows->inventory_window, 0, 0);
	wnoutrefresh(windows->inventory_window);

	doupdate(); // This function is used to refresh the screen with any buffer changes that have been made
}

void printMapInWindow(Game * game, Windows * windows)
{
    Dimensions game_window;

    //game_window.height = (0.75)*windows->main_dimensions.height;
    //game_window.width = (0.70)*windows->main_dimensions.width;

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
}

