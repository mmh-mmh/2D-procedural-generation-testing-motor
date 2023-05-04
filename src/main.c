#include "valley.h"


int main(int argc, char ** argv)
{
	
	mainSetup();

	/*loading();*/
	
	menuLoop();

	Level * level = createLevel();
	
	WINDOW * gameWindow = gameWindowSetup(GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH, GAME_WINDOW_POSITION_Y, GAME_WINDOW_POSITION_X);
	
	
	char input;
	
	//main game loop
	while ( (input = getch()) != 'a')
	{
		
		//change the player position
		handlePlayerInput(level->player, input, level->map, level->mapSave);

		//draw map arround the player, in the window's boundaries
		drawMapInGameWindow(gameWindow, level->map, level->player);
	}

	free(level);
	
	endwin();
}


int mainSetup()
{
	start_color();
	use_default_colors();

	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
}

/*
void loading()
{
    printf("\033[8;100;200t"); // ajuste la taille de la fenêtre
    printf("\033[2J"); // nettoie l'écran
    printf("\033[1;31m"); // change la couleur du texte en rouge

    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("      V     V    AAAA    L          L     EEEEEEE   Y     Y\n");
    printf("      V     V   A    A   L          L     E         Y   Y \n");
    printf("      V     V  AAAAAAAA  L          L     EEEEE      Y Y  \n");
    printf("       V   V   A      A  L          L     E           Y   \n");
    printf("        V V    A      A  LLLLLLLLL  LLLLL EEEEEEE     Y   \n");

    sleep(5); // pause pendant 5 secondes
	printf("\033[0m"); // remet la couleur du texte à la normale
    printf("\033[2J"); // nettoie l'écran
    printf("\033[0;0H");
}
*/