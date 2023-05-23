#include "valley.h"

void loading(Windows* windows)
{
    windows->loading_window = derwin(windows->main_window,9, 95, ((0.5) * windows->main_dimensions.height) - 14, ((0.5) * windows->main_dimensions.width) - 45);

    const char* text = " __    __     _                            _                     _ _            \n"
                       "       / / /\\ \\ \\___| | ___ ___  _ __ ___   ___  | |_ ___   /\\   /\\__ _| | | ___ _   _ \n"
                       "       \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  \\ \\ / / _` | | |/ _ \\ | | |\n"
                       "        \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |  \\ V / (_| | | |  __/ |_| |\n"
                       "         \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/    \\_/ \\__,_|_|_|\\___|\\__, |\n"
                       "                                                                                  |___/ ";
    int loading_y = 1;
    int loading_x =7;
    box(windows->loading_window, 1, 0);

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '\n')
        {
            loading_y++;
            loading_x = 0;
        }
        else
        {
            mvwprintw(windows->loading_window, loading_y, loading_x, "%c", text[i]);
            loading_x++;
        }
        usleep(1000);
        wrefresh(windows->loading_window);
    }
    mvprintw(((0.5) * windows->main_dimensions.height) - 7, ((0.5) * windows->main_dimensions.width) - 10, "Press enter to continue");
    refresh();
    while (getch() != 10)
    {
    }
}