#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#define MAP_HEIGHT 51
#define MAP_WIDTH 101

#define MAIN_WINDOW_HEIGHT 21
#define MAIN_WINDOW_WIDTH 101
#define MAIN_WINDOW_POSITION_Y 1
#define MAIN_WINDOW_POSITION_X 3

#define HOUSE_MINIMAL_DISTANCE 50


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

typedef struct House
{	
	Position position;
	Dimensions dimensions;

	Position door_position;
} House;

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

typedef struct Game
{
	Map * map;
	PlayerStruct * player;
	House * house;
} Game;


//game functions 
Game * gameSetup();
void gameLoop(WINDOW * main_window);

//main functions
void screenSetup();

//player functions
PlayerStruct * playerSetup();
void setRandomSpawn(Game * game);
Position handleInput(int input);
void checkPosition(Position position_offset, Game * game);
void playerMove(Position position_offset, Game * game);

//map functions
Map * createMap();
void mapSetup(Map * map);
char ** copyMap(Map * map);
void placePlayerAndStructures(Game * game);

//house functnions
void generateRandomHouseDimensionsBetweenTwoNumbers (House * house, int num1, int num2);
void generateRandomHousePosition (Game * game);
void placeHouseAtPlayerDistance (Game * game, int distance_limit, int * trials, int * max_trials);
bool isHouseTooNear(Game * game, int distance_limit);
void generateHouse(Game * game);
bool isHouseStuck(Game * game);
bool isHouseUpLeftCornerReachable(Game * game);
bool isHouseReachable(Game * game);


//procedural functions
void mapProceduralGeneration(Map * map);
void mapNoiseGeneration(Map * map, int density);
void mapApplyCellularAutomaton(Map * map, int count);
void mapFillWalls(Map * map);
void mapGrassGeneration(Map * map);

//pathfinding functions
bool isHouseUpLeftCornerReachable(Game * game);

//window functions
WINDOW * CreateMainWindow();

//render functions
void render(Game * game, WINDOW * main_window);
void drawMapInGameWindow(Game * game, WINDOW * gameWindow);

#endif
