#include "valley.h"

void loading(Windows * windows)
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

void endLoading(Windows * windows, int end_condition)
{
    clear();
    refresh();
    const char* time = "$$$$$$$$\\                         $$$$$$\\  $$\\                         \n"
                      "\\__$$  __|                       $$  __$$\\ $$ |                        \n"
                      "   $$ | $$$$$$\\   $$$$$$\\        $$ /  \\__|$$ | $$$$$$\\  $$\\  $$\\  $$\\ \n"
                      "   $$ |$$  __$$\\ $$  __$$\\       \\$$$$$$\\  $$ |$$  __$$\\ $$ | $$ | $$ |\n"
                      "   $$ |$$ /  $$ |$$ /  $$ |       \\____$$\\ $$ |$$ /  $$ |$$ | $$ | $$ |\n"
                      "   $$ |$$ |  $$ |$$ |  $$ |      $$\\   $$ |$$ |$$ |  $$ |$$ | $$ | $$ |\n"
                      "   $$ |\\$$$$$$  |\\$$$$$$  |      \\$$$$$$  |$$ |\\$$$$$$  |\\$$$$$\\$$$$  |\n"
                      "   \\__| \\______/  \\______/        \\______/ \\__| \\______/  \\____\\____/ \n";

    const char* quest = "                                                               \n"
                      " __ __            _____            _____    _____             \n"
                      "|  |  |___ _ _   |  _  |___ ___   |  _  |  |  |  |___ ___ ___ \n"
                      "|_   _| . | | |  |     |  _| -_|  |     |  |     | -_|  _| . |\n"
                      "  |_| |___|___|  |__|__|_| |___|  |__|__|  |__|__|___|_| |___|\n"
                      "                                                               \n";
    
    const char* score = "___  ___             _____                      _ _ _ \n"
                      "|  \\/  |            /  ___|                    | | | |\n"
                      "| .  . | __ ___  __ \\ `--.  ___ ___  _ __ ___  | | | |\n"
                      "| |\\/| |/ _` \\ \\/ /  `--. \\/ __/ _ \\| '__/ _ \\ | | | |\n"
                      "| |  | | (_| |>  <  /\\__/ / (_| (_) | | |  __/ |_|_|_|\n"
                      "\\_|  |_/\\__,_/_/\\_\\ \\____/ \\___\\___/|_|  \\___| (_|_|_)\n"
                      "                                                      \n";

    const char* dead = " __     __           _____  _          _ \n"
                  " \\ \\   / /          |  __ \\(_)        | |\n"
                  "  \\ \\_/ /__  _   _  | |  | |_  ___  __| |\n"
                  "   \\   / _ \\| | | | | |  | | |/ _ \\/ _` |\n"
                  "    | | (_) | |_| | | |__| | |  __/ (_| |\n"
                  "    |_|\\___/ \\__,_| |_____/|_|\\___|\\__,_|\n";

    const char* necromancer = "   ___      _      __ _             ___                      _            \n"
                  "  | _ )    (_)    / _` |    o O O  | _ )     _ _   __ _     (_)    _ _    \n"
                  "  | _ \\    | |    \\__, |   o       | _ \\    | '_| / _` |    | |   | ' \\   \n"
                  "  |___/   _|_|_   |___/   TS__[O]  |___/   _|_|_  \\__,_|   _|_|_  |_||_|  \n"
                  "_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| {======|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|\n"
                  "\"`-0-0-'\"`-0-0-'\"`-0-0-'./o--000'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\n";


    switch (end_condition)
    {
        case 1:
            for(int i = 0; i<strlen(time); i++)
        {
                printw("%c", time[i]);
                usleep(1000);
                refresh();
            }  
            sleep(3);
            break;                                                     
        case 2:
            for(int i = 0; i<strlen(quest); i++)
        {
                printw("%c", quest[i]);
                usleep(1000);
                refresh();
            } 
            sleep(3);         
            break;
        case 3:
            for(int i = 0; i<strlen(score); i++)
        {
                printw("%c", score[i]);
                usleep(1000);
                refresh();
            } 
            sleep(3);         
            break;
        case 4:
            for(int i = 0; i<strlen(dead); i++)
            {
                printw("%c", dead[i]);
                usleep(1000);
                refresh();
            } 
            sleep(3);         
            break;   
    case 5:
            for(int i = 0; i<strlen(necromancer); i++)
            {
                printw("%c", necromancer[i]);
                usleep(1000);
                refresh();
            } 
            sleep(3);         
            break;
    }   
    return; 
}