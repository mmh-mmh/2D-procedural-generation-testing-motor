#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "inventory.h"
#include "mainMenu.h"

#define MAP_HEIGHT 41
#define MAP_WIDTH 81

#define GAME_WINDOW_HEIGHT 21
#define GAME_WINDOW_WIDTH 51
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

typedef struct Dimension
{
	int height;
	int width;
} Dimension;

typedef struct PlayerStruct
{
	Position position;
	char skin;
	int health;
	Item ** backpack;
} PlayerStruct;

typedef struct Level
{
	char ** map;
	char ** mapSave;

	Position * HousePosition;

	PlayerStruct * player;

	//MonsterStruct ** monsters;
	//int numberOfMonsters;
} Level;


//level fonctions 
Level * createLevel();

//main fonctions
int mainSetup();
void loading();

//menu fonctions;
void closeMenu(int numberItems, MENU * menu, ITEM ** items);
int mainMenu(int numberItems, char * choices[]);
void menuLoop();

//player fonctions
PlayerStruct * playerSetup(int y, int x);
int handlePlayerInput(PlayerStruct * player, char input, char ** map, char ** mapInmovableSave);
int playerMove(PlayerStruct * player, Position posDiff, char ** map, char ** mapInmovableSave);
int handleMovable(PlayerStruct * player, Position posDiff, char ** map, char ** mapInmovableSave);

//map fonctions
char ** mapSetup(int height, int width);
int mapNotMovableGeneration(Level * level);
int mapMovableGeneration(char ** map);
int drawMapInGameWindow(WINDOW * window, char ** map, PlayerStruct * player);
int mapRandGrassGeneration(char ** map);
int mapRandHouseGeneration(Level * level);
int mapRandRockGeneration(char ** map);
int mapRandMovableGeneration(char ** map);
int unblockDoor(char ** map, Position * doorPos);
char ** saveMap(char ** map);

//window fonctions
WINDOW * gameWindowSetup(int height, int width, int y, int x);

#endif
