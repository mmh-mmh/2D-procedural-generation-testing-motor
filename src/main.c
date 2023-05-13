#include "valley.h"


int main()
{
	screenSetup();
	mainLoops();

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

	srand(time(NULL));
}

void mainLoops()
{
	WINDOW * main_window = CreateMainWindow();

	//menuLoop();
	gameLoop(main_window);
}