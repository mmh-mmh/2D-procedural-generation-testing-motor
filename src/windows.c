#include "valley.h"

Windows * windowsSetup()
{	
	Windows * windows = malloc(sizeof(Windows));
	int main_height = MAIN_WINDOW_HEIGHT;
	int main_width = MAIN_WINDOW_WIDTH;
	int main_y = MAIN_WINDOW_POSITION_Y;
	int main_x = MAIN_WINDOW_POSITION_X;

	windows->main_window = newwin(main_height, main_width, main_y, main_x);
	windows->game_window = derwin(windows->main_window, (0.95)*main_height, (0.99)*main_width, 1, 1);

	if (windows->game_window == NULL) {
    fprintf(stderr, "Failed to create game window\n");
    exit(1);
	}

	return windows;
}