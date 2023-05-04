#include "valley.h"

void closeMenu(int numberItems, MENU * menu, ITEM ** items)
{
    unpost_menu(menu);
    free_menu(menu);

    for (int i = 0; i < numberItems; i++)
    {
        free_item(items[i]);
    }
}

int mainMenu(int numberItems, char * choices[])
{
    MENU * menu;
    ITEM ** items = malloc(sizeof(**items)*numberItems);
    ITEM * current;
    int i, c, value, x, y;


    for(i = 0; i < numberItems; i++)
    {
        items[i]= new_item(choices[i],"");
    }
    items[i] = NULL;

    menu = new_menu((ITEM**)items);
    WINDOW * menuwin = newwin(MENU_WINDOW_HEIGHT, MENU_WINDOW_WIDTH, MENU_WINDOW_POSITION_Y, MENU_WINDOW_POSITION_X);
    keypad(menuwin, TRUE);

    //associer la fenêtre au menu
    set_menu_win(menu, menuwin);
    //créer une sous-fenêtre pour les options
    set_menu_sub(menu, derwin(menuwin, numberItems+2, 28, 1, 1));
    //afficher les options sur une seule colonne
    set_menu_format(menu, numberItems, 1);
    post_menu(menu);
    wrefresh(menuwin);

    

    while(true)
    {   
        wborder(menuwin, -1, -1, -1, -1, -1, -1, -1, -1);
        wresize(menuwin, MENU_WINDOW_HEIGHT, MENU_WINDOW_WIDTH);

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


void menuLoop()
{
    char * choices[] = {"Start a new adventure !", "Continue at your last checkpoint", "Quit game"};
    int choice = -1;
    while(choice !=0)
    {
        choice = mainMenu(3, choices);

        switch(choice)
        {
            case 0:
                break;
            case 1:
                //on mettra un truc apres avoir trouver un moyen de sauvegarder 
            case 2:
                endwin(); 
                exit(0);
        }
    }
}