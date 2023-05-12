#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAP_HEIGHT 81
#define MAP_WIDTH 161

#define GAME_WINDOW_HEIGHT 21
#define GAME_WINDOW_WIDTH 101
#define GAME_WINDOW_POSITION_Y 1
#define GAME_WINDOW_POSITION_X 3

#define PLAYER_START_POSITION_Y MAP_HEIGHT/2
#define PLAYER_START_POSITION_X MAP_WIDTH/2

#define HOUSE_SIZE 11


typedef struct Position
{
	int y;
	int x;
} Position;

typedef struct Dimensions
{
	int height;
	int width;
} Dimensions;

typedef struct PlayerStruct
{
	Position position;
	char skin;
} PlayerStruct;

typedef struct Level
{
	char ** map;
	char ** mapSave;
	Position ** mapDoors;

	Position ** houseDoors;

	PlayerStruct * player;
} Level;


//level fonctions 
Level * createLevel();

//main fonctions
int mainSetup();
void loading();

//player fonctions
PlayerStruct * playerSetup(int y, int x);
int handlePlayerInput(PlayerStruct * player, char input, char ** map, char ** mapInmovableSave);
int playerMove(PlayerStruct * player, Position posDiff, char ** map, char ** mapInmovableSave);

//map fonctions
char ** mapSetup(int height, int width, Level * level);
int mapGeneration(Level * level);

int houseGeneration(Level * level);


int drawMapInGameWindow(WINDOW * window, char ** map, PlayerStruct * player);

//window fonctions
WINDOW * gameWindowSetup(int height, int width, int y, int x);

#endif
