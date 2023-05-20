#include "valley.h"

void loading(Windows * windows)
{
    const char* text = "                        __    __     _                            _                     _ _            \n"
        "                       / / /\\ \\ \\___| | ___ ___  _ __ ___   ___  | |_ ___   /\\   /\\__ _| | | ___ _   _ \n"
        "                       \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  \\ \\ / / _` | | |/ _ \\ | | |\n"
        "                        \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |  \\ V / (_| | | |  __/ |_| |\n"
        "                         \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/    \\_/ \\__,_|_|_|\\___|\\__, |\n"
        "                                                                                                 |___/ ";
        for(int i = 0; i<strlen(text); i++)
        {
                printw("%c", text[i]);
                usleep(10000);
                refresh();
            }
        mvprintw(((0.5)*windows->main_dimensions.height)-8, ((0.5)*windows->main_dimensions.width)-10, "Press enter to continu");
        refresh();
    while(getch()!=10){

    }
    //clear();
    //refresh();
}