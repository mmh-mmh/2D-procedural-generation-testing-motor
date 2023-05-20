#include "valley.h"

void menuLoop(Windows * windows)
{
    char * choices[] = {"Start a new adventure !", "Need some help ?", "Continue at your last checkpoint", "Quit game"};
    int choice = -1;
    while(choice !=0)
    {
        choice = mainMenu(windows, 4, choices);
        refresh();

        switch(choice)
        {
            case 0:
                break;
            case 1:
                clear();
                printw("Segmentation fault");
                refresh();
                sleep(3);
                clear();
                printw("It was a joke :)");
                refresh();
                sleep(3);
                clear();
                mvwprintw(windows->main_window, 0, 0, "Z:aller vers le haut");
                mvwprintw(windows->main_window, 1, 0, "Q:aller vers la gauche");
                mvwprintw(windows->main_window, 2, 0, "S:aller vers le bas");
                mvwprintw(windows->main_window, 3, 0, "D:aller vers la droite");
                refresh();
                sleep(4);
                clear();
                break;
            case 2:
                //on mettra un truc apres avoir trouver un moyen de sauvegarder 
            case 3:
                endwin(); 
                exit(0);
        }
    }
}

void closeMenu(int numberItems, MENU * menu, ITEM ** items)
{
    clear();
    free_menu(menu);

    for (int i = 0; i < numberItems; i++)
    {
        free_item(items[i]);
    }
}

int mainMenu(Windows * windows, int numberItems, char * choices[])
{

    MENU * menu;
    ITEM ** items = malloc(sizeof(*items)*numberItems);

    ITEM * current;
    int i, c, value, x, y;

    for(i = 0; i < numberItems; i++)
    {
        items[i]= new_item(choices[i],"");
    }
    items[i] = NULL;

    menu = new_menu((ITEM**)items);

    int menu_width = 40;
    int menu_height = 10;
    int menu_y = ((0.5)*windows->main_dimensions.height) - (menu_height/2);
    int menu_x = ((0.5)*windows->main_dimensions.width) - (menu_width/2);

    WINDOW * menuwin = derwin(windows->main_window, menu_height, menu_width, menu_y, menu_x);
    keypad(menuwin, TRUE);

    
    set_menu_win(menu, menuwin); //associer la fenêtre au menu
    
    set_menu_sub(menu, derwin(menuwin, numberItems+2, 28, 1, 1)); //créer une sous-fenêtre pour les options
 
    set_menu_format(menu, numberItems, 1); //afficher les options sur une seule colonne
    post_menu(menu);
    wrefresh(menuwin);



    while(true)
    {
        wborder(menuwin, -1, -1, -1, -1, -1, -1, -1, -1);
        wresize(menuwin, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH);

        c = wgetch(menuwin);
        switch(c)
        {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
                
            //entrer = 10 en ASCII
            case 10:
                current = current_item(menu);
                value = item_index(current);
                closeMenu(numberItems, menu, items);
                delwin(menuwin);
                return value;
        }

    wrefresh(menuwin);
    }
}