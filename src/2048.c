#include "valley.h"

int add_random_tile(int ** tab) {
    int empty_tiles = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (tab[i][k] == 0) {
                empty_tiles++;
            }
        }
    }
    if (empty_tiles == 0) {
        return 0;
    }
    int tile_index = rand() % empty_tiles;
    int value = rand() % 100 < 90 ? 2 : 4;
    empty_tiles = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (tab[i][k] == 0) {
                if (empty_tiles == tile_index) {
                    tab[i][k] = value;
                    return 0;
                }
                empty_tiles++;
            }
        }
    }
}

int ** init_board() {

    int ** tab = malloc(sizeof(int*)*BOARD_SIZE);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        tab[i] = malloc(sizeof(int)* BOARD_SIZE);

        for (int k = 0; k < BOARD_SIZE; k++) {
            tab[i][k] = 0;
        }
    }
    add_random_tile(tab);
	add_random_tile(tab);

    return tab;
}

void print_board(int ** tab, Windows * windows){
	wclear(windows->game_window);
    box(windows->game_window, 0, 0);
	

    Dimensions game_window;
    getmaxyx(windows->game_window, game_window.height, game_window.width);

	
	for(int i=0;i<BOARD_SIZE;i++){
		for(int k=0;k<BOARD_SIZE;k++){
			
			
			switch(tab[i][k]){
				
				case 0 :
					wattron(windows->game_window, COLOR_PAIR(DEFAULT_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(DEFAULT_ON_DEFAULT));
					break;
				case 2 :
					wattron(windows->game_window, COLOR_PAIR(YELLOW_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(YELLOW_ON_DEFAULT));
					break;
				case 4 :
					wattron(windows->game_window, COLOR_PAIR(YELLOW_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(YELLOW_ON_DEFAULT));
					break;
				case 8 :
					wattron(windows->game_window, COLOR_PAIR(GREEN_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(GREEN_ON_DEFAULT));
					break;
				case 16 :
					wattron(windows->game_window, COLOR_PAIR(GREEN_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(GREEN_ON_DEFAULT));
					break;
				case 32 :
					wattron(windows->game_window, COLOR_PAIR(BLUE_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(BLUE_ON_DEFAULT));
					break;
				case 64 :
					wattron(windows->game_window, COLOR_PAIR(MAGENTA_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(MAGENTA_ON_DEFAULT));
					break;
				case 128 :
					wattron(windows->game_window, COLOR_PAIR(RED_ON_DEFAULT));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(RED_ON_DEFAULT));
					break;
				case 256 :
					wattron(windows->game_window, COLOR_PAIR(BLACK_ON_WHITE));
					mvwprintw(windows->game_window, (game_window.height)/2 + i, (game_window.width)/4 + k*3, "%d", tab[i][k]);
					wattroff(windows->game_window, COLOR_PAIR(BLACK_ON_WHITE));
					break;
                    
			}
		}
        wrefresh(windows->game_window);
	}
}

void make_move(int ** tab, char move){

	switch(move){
		case 'd':
        case 'D':
			for(int i=0;i<BOARD_SIZE;i++){
				for(int k=BOARD_SIZE-2;k>=0;k--){
					if(tab[i][k]!=0){
						int kn=k;
						while(kn<BOARD_SIZE-1){
								if(tab[i][kn+1]==0){
									tab[i][kn+1]=tab[i][kn];
									tab[i][kn]=0;
									kn++;
								}
								else if(tab[i][kn+1]==tab[i][kn]){
									tab[i][kn+1]*=2;
									tab[i][kn]=0;
									break;
								}
								else{
									break;
								}
						}
					}
				}
			}
		break;
		case 'q':
        case 'Q':
			for(int i=0;i<BOARD_SIZE;i++){
				for(int k=1;k<BOARD_SIZE;k++){
					if(tab[i][k]!=0){
						int kn=k;
						while(kn>0){
								if(tab[i][kn-1]==0){
									tab[i][kn-1]=tab[i][kn];
									tab[i][kn]=0;
									kn--;
								}
								else if(tab[i][kn-1]==tab[i][kn]){
									tab[i][kn-1]*=2;
									tab[i][kn]=0;
									break;
								}
								else{
									break;
								}
						}
					}	
				}
			}
		break;
		case 's':
        case 'S':
			for(int k=0;k<BOARD_SIZE;k++){
				for(int i=BOARD_SIZE-2;i>=0;i--){
				
				
					if(tab[i][k]!=0){
						int in=i;
						while(in<BOARD_SIZE-1){
								if(tab[in+1][k]==0){
									tab[in+1][k]=tab[in][k];
									tab[in][k]=0;
									in++;
								}
								else if(tab[in+1][k]==tab[in][k]){
									tab[in+1][k]*=2;
									tab[in][k]=0;
									break;
								}
								else{
									in=BOARD_SIZE-2;
									break;
								}
						}
					}	
					
					
					
				}
			}
		break;
		case 'z':
        case 'Z':
			for(int k=0;k<BOARD_SIZE;k++){
				for(int i=1;i<BOARD_SIZE;i++){
					if(tab[i][k]!=0){
						int in=i;
						while(in>0){
								if(tab[in-1][k]==0){
									tab[in-1][k]=tab[in][k];
									tab[in][k]=0;
									in--;
								}
								else if(tab[in-1][k]==tab[in][k]){
									tab[in-1][k]*=2;
									tab[in][k]=0;
									break;
								}
								else{
									break;
								}
						}	
					}
				}
			}
		break;
	}
}



bool check_win(int ** tab) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (tab[i][k] == WIN_SCORE) {
                return true;
            }
        }
    }
    return false;
}

bool check_loss(int ** tab) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (tab[i][k] == 0) {
                return false;
            }
            if (i < BOARD_SIZE-1 && tab[i][k] == tab[i+1][k]) {
                return false;
            }
            if (k < BOARD_SIZE-1 && tab[i][k] == tab[i][k+1]) {
                return false;
            }
        }
    }
    return true;
}

int play2048(Windows * windows){

    int ** tab = init_board();
    char move;
	

	while (true) {
		print_board(tab, windows);
		
		if (check_loss(tab)) {
			getch();
            free_board(tab);
        	return 0;
            
		}
		else if (check_win(tab)) {
			getch();
            free_board(tab);
			return 1;
            
		}
		
		do {
			move = getch();
		} while (move != 'z' && move != 'Z' && move !=  'q' && move != 'Q' &&  move!= 's' &&  move!= 'S' &&  move!= 'd' &&  move!= 'D');
		
		make_move(tab, move);
		add_random_tile(tab);
	}
}

void free_board(int **tab) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(tab[i]);
    }
    free(tab);
}