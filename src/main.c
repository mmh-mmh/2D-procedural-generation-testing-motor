#include "valley.h"


int main()
{
	screenSetup();

	WINDOW * main_window = CreateMainWindow();

	//menuLoop();
	gameLoop(main_window);

	endwin();

	return 0;
}


void screenSetup()
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	refresh();

	start_color();
	use_default_colors();
	init_pair(1, COLOR_GREEN, -1);
	init_pair(2, COLOR_WHITE, -1);
	init_pair(3, COLOR_RED, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(5, COLOR_YELLOW, -1);
	init_pair(6, COLOR_MAGENTA, -1);
	init_pair(7, COLOR_CYAN, -1);
	


	srand(time(NULL));
}