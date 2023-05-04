#include "valley.h"


int main(int argc, char ** argv)
{
	
	mainSetup();

	Level * level = createLevel();
	
	WINDOW * gameWindow = gameWindowSetup(GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH, GAME_WINDOW_POSITION_Y, GAME_WINDOW_POSITION_X);
	
	
	char input;
	
	//main game loop
	while ( (input = getch()) != 'a')
	{
		
		//change the player position
		handlePlayerInput(level->player, input, level->map, level->mapSave);

		//draw map arround the player, in the window's boundaries
		drawMapInGameWindow(gameWindow, level->map, level->player);
	}

	free(level);
	
	endwin();
}


int mainSetup()
{
	start_color();
	use_default_colors();

	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
}