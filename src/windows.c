#include "valley.h"

Windows* windowsSetup()
{   
    Windows * windows = malloc(sizeof(Windows));

    windows->main_dimensions.height = MAIN_WINDOW_HEIGHT;
    windows->main_dimensions.width = MAIN_WINDOW_WIDTH;
    windows->main_position.y = MAIN_WINDOW_POSITION_Y;
    windows->main_position.x = MAIN_WINDOW_POSITION_X;


    windows->main_window = newwin(windows->main_dimensions.height, windows->main_dimensions.width, windows->main_position.y, windows->main_position.x);


    int game_height = (0.75)*windows->main_dimensions.height; 
    int game_width = (0.70)*windows->main_dimensions.width;      
    int game_y = 0;                         
    int game_x = 0;                         

    windows->game_window = derwin(windows->main_window, game_height, game_width, game_y, game_x);


    int text_height = (0.25)*windows->main_dimensions.height;
    int text_width = (0.70)*windows->main_dimensions.width;
    int text_y = game_height;
    int text_x = 0;

    windows->text_window = derwin(windows->main_window, text_height, text_width, text_y, text_x);


	int stats_height = (0.5)*windows->main_dimensions.height;
	int stats_width = (0.30)*windows->main_dimensions.width;
	int stats_y = 0;
	int stats_x = game_width;

    windows->stats_window = derwin(windows->main_window, stats_height, stats_width, stats_y, stats_x);

    
    int inventory_height = ((0.5)*windows->main_dimensions.height);
    int inventory_width = (0.30)*windows->main_dimensions.width;
    int inventory_y = stats_height;
    int inventory_x = game_width;

    windows->inventory_window = derwin(windows->main_window, inventory_height, inventory_width, inventory_y, inventory_x);


    if (windows->game_window == NULL) {
        fprintf(stderr, "Failed to create game window\n");
        exit(1);
    }
    if (windows->text_window == NULL) {
        fprintf(stderr, "Failed to create text window\n");
        exit(1);
    }
    if (windows->stats_window == NULL) {
        fprintf(stderr, "Failed to create stats window\n");
        exit(1);
    }
    if (windows->inventory_window == NULL) {
        fprintf(stderr, "Failed to create inventory window\n");
        exit(1);
    }

    return windows;
}
