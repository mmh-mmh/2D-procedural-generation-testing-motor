#include "valley.h"

Windows* windowsSetup()
{   
    Windows * windows = malloc(sizeof(Windows));

    int main_height = MAIN_WINDOW_HEIGHT;
    int main_width = MAIN_WINDOW_WIDTH;
    int main_y = MAIN_WINDOW_POSITION_Y;
    int main_x = MAIN_WINDOW_POSITION_X;

    windows->main_window = newwin(main_height, main_width, main_y, main_x);

    int game_height = (0.75)*main_height;  // 3/4 of the height
    int game_width = main_width;            // same width
    int game_y = 0;                         // starting from the top
    int game_x = 0;                         // starting from the left
    windows->game_window = derwin(windows->main_window, game_height, game_width, game_y, game_x);

    int text_height = main_height - game_height; // remaining height
    int text_width = main_width;                 // same width
    int text_y = game_height;                    // starting from where game_window ends
    int text_x = 0;                              // starting from the left
    windows->text_window = derwin(windows->main_window, text_height, text_width, text_y, text_x);

    if (windows->game_window == NULL) {
        fprintf(stderr, "Failed to create game window\n");
        exit(1);
    }
    if (windows->text_window == NULL) {
        fprintf(stderr, "Failed to create text window\n");
        exit(1);
    }

    return windows;
}
