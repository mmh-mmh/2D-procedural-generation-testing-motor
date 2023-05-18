#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

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
	int ** colors;
} Map;

typedef struct PlayerStruct
{
	Position position;
	char skin;
} PlayerStruct;

typedef struct MobStruct
{
    Position coordinate;
    int health;
    int attack;
    char skin;
} MobStruct;

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
void SetRandomSpawn(Game * game);
Position handleInput(int input);
void checkPosition(Position position_offset, Game * game);
void playerMove(Position position_offset, Game * game);

//mob functions

MobStruct * genMonster( char *map[MAP_WIDTH],int health, int attack, char skin);
MobStruct * MobSetUp(int mobtype, char ** map);
void AddMob(char *map[MAP_WIDTH]);
Position genPos(char *map[MAP_WIDTH], char skin, int height,int width);
Position findEmptyZoneStart(char *map[MAP_WIDTH], int height, int width);
bool IsPositionValid(Position pos, int gap, char skin, int height, int width, char *map[MAP_WIDTH]);






//map functions
Map * createMap();
void mapSetup(Map * map);
char ** copyMap(Map * map);

//procedural functions
void mapProceduralGeneration(Map * map);
void mapNoiseGeneration(Map * map, int density);
void mapApplyCellularAutomaton();
void mapFillWalls(Map * map);
void mapGrassGeneration(Map * map);

//window functions
WINDOW * CreateMainWindow();

//render functions
void render(Game * game, WINDOW * main_window);
void drawMapInGameWindow(Game * game, WINDOW * gameWindow);

#endif
