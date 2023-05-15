#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#define MAP_HEIGHT 80
#define MAP_WIDTH 160

#define MAIN_WINDOW_HEIGHT 21
#define MAIN_WINDOW_WIDTH 101
#define MAIN_WINDOW_POSITION_Y 1
#define MAIN_WINDOW_POSITION_X 3

#define NOISE_DENSITY 60
#define CELLULAR_AUTOMATON_ITERATIONS 12

#define HOUSE_SIZE 6

#define HOUSE_MINIMAL_DISTANCE 20


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

typedef struct Windows
{
	WINDOW * main_window;
	WINDOW * game_window;
	//WINDOW * text_window;
	//WINDOW * inventory_window;
} Windows;


//game functions 
Game * gameSetup();
void gameLoop(Windows * windows);

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
Windows * windowsSetup();

//render functions
void render(Game * game, Windows * windows);
void drawMapInGameWindow(Game * game, Windows * windows);

//error functions
void CheckConstants();

#endif
