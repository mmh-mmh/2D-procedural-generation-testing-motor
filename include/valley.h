#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAP_HEIGHT 81
#define MAP_WIDTH 161

#define MAIN_WINDOW_HEIGHT 21
#define MAIN_WINDOW_WIDTH 101
#define MAIN_WINDOW_POSITION_Y 1
#define MAIN_WINDOW_POSITION_X 3

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

typedef struct Map
{
    Dimensions dimensions;
    char ** tiles;
} Map;

typedef struct PlayerStruct
{
	Position position;
	char skin;
} PlayerStruct;

typedef struct Game
{
	Map * map;
	PlayerStruct * player;
} Game;


//game fonctions 
Game * gameSetup();
void gameLoop(WINDOW * main_window);

//main fonctions
void screenSetup();
void mainLoops();

//player fonctions
PlayerStruct * playerSetup();
Position handleInput(int input);
void checkPosition(Position position_offset, Game * game);
void playerMove(Position position_offset, Game * game);


//map fonctions
Map * createMap();
char ** mapSetup(Map * map);
void mapProceduralGeneration(Map * map);

//window fonctions
WINDOW * CreateMainWindow();

//render fonctions
void render(Game * game, WINDOW * main_window);
void drawMapInGameWindow(Game * game, WINDOW * gameWindow);

#endif
