#include "valley.h"

WINDOW * CreateMainWindow()
{
	WINDOW * newGameWindow = malloc(sizeof(WINDOW));
	newGameWindow = newwin(MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH, MAIN_WINDOW_POSITION_Y, MAIN_WINDOW_POSITION_X);
	return newGameWindow;
}
