#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAP_HEIGHT 161
#define MAP_WIDTH 321

#define MAIN_WINDOW_HEIGHT 31
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
typedef MobStruct
{
    Position coordinate;
    int health;
    int damage;
    char skin;
}MobStruct;

typedef struct Game
{
	Map * map;
	PlayerStruct * player;
} Game;


//game functions
Game * gameSetup();
void gameLoop(WINDOW * main_window);

//main functions
void screenSetup();
void mainLoops();

//player functions
PlayerStruct * playerSetup();
Position handleInput(int input);
void checkPosition(Position position_offset, Game * game);
void playerMove(Position position_offset, Game * game);

//mob functions
MobStruct * genMonster( int health, int attack, char skin);
MobStruct * Mobselect(int mobtype);
//map functions
Map * createMap();
char ** mapSetup(Map * map);
char ** copyMap(Map * map);

//procedural functions
void mapProceduralGeneration(Map * map);
void mapNoiseGeneration(Map * map, int density);
void mapApplyCellularAutomaton();
void mapFillWalls(Map * map);

//window functions
WINDOW * CreateMainWindow();

//render functions
void render(Game * game, WINDOW * main_window);
void drawMapInGameWindow(Game * game, WINDOW * gameWindow);

#endif
