#ifndef VALLEY_H
#define VALLEY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <menu.h>
#include <string.h>

#define MAP_HEIGHT 30
#define MAP_WIDTH 60

#define MAIN_WINDOW_HEIGHT 26
#define MAIN_WINDOW_WIDTH 101
#define MAIN_WINDOW_POSITION_Y 1
#define MAIN_WINDOW_POSITION_X 3

#define NOISE_DENSITY 60
#define CELLULAR_AUTOMATON_ITERATIONS 12

#define HOUSE_SIZE 6

#define HOUSE_MINIMAL_DISTANCE 9

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

typedef struct HouseStruct
{	
	Position position;
	Dimensions dimensions;
	Position door_position;
} HouseStruct;

typedef struct Map
{
    Dimensions dimensions;
    char ** tiles;
	int ** colors;
} Map;

typedef struct MobStruct
{
    Position coordinate;
    int health;
    int attack;
    char skin;
} MobStruct;

typedef struct npcStruct
{
	char * name;
	char skin;
	Position position;
} npcStruct;

typedef enum{WEAPON_TYPE, OBJECTS_TYPE,POTIONS_TYPE}itemType;

typedef struct Weaponstats
{
	int damage;
	int durability;
} Weaponstats; 

typedef struct Object
{
	Position * coordinate;
	char skin;
	int quantity;
} Object;

typedef struct Potion
{
	int heal;
	int quantity;
} Potion;

typedef struct Item
{
	itemType type;
	union
	{
		Weaponstats * weapon;
		Object * object;
		Potion * potions;
	}mainItems;
	char name[256];
} Item;

typedef struct PlayerStruct
{
	Position position;
	char skin;
	int health;
    int max_health;
	Item ** backpack;
    int score;
} PlayerStruct;

typedef struct Game
{
	Map * map;
	PlayerStruct * player;
	HouseStruct * house;
	npcStruct * npc;
} Game;

typedef struct Windows
{
	Position main_position;
	Dimensions main_dimensions;
	WINDOW * main_window;
	WINDOW * game_window;
	WINDOW * text_window;
	WINDOW * stats_window;
	WINDOW * inventory_window;
} Windows;




//game functions 
Game * gameSetup();
void gameLoop(Windows * windows);

//menu functions
void menuLoop(Windows * windows);
int mainMenu(Windows * windows, int numberItems, char * choices[]);
void closeMenu(int numberItems, MENU * menu, ITEM ** items);

//main functions
void screenSetup();

//player functions
PlayerStruct * playerSetup();
void setRandomSpawn(Game * game);
Position handleInput(int input);
void checkPosition(Position position_offset, Game * game, Windows * window);
void playerMove(Position position_offset, Game * game);

//npc functions
npcStruct * wizardSetup();
void placeWizardInHouse(Game * game);
void giveQuest(Game * game, Windows * windows);

// mob functions
MobStruct * genMonster(Map * map, int health, int attack, char skin);

//map functions
Map * createMap();
void mapSetup(Map * map);
char ** copyMap(Map * map);
bool TryToPlaceHouseAndPlayerForMaxTrials(Game * game, int max_trials);

//house functnions
HouseStruct * houseSetup();
void generateRandomHousePosition (Game * game);
void generateHouse(Game * game);
bool isHouseStuck(Game * game);
bool isHouseReachable(Game * game);

//procedural functions
void mapProceduralGeneration(Map * map);
void mapNoiseGeneration(Map * map, int density);
void mapApplyCellularAutomaton(Map * map, int count);
void mapFillWalls(Map * map);
void mapGroundGeneration(Map * map);
void mapFlowersGeneration(Map * map);

//pathfinding functions
bool isHouseUpLeftCornerReachable(Game * game);

//window functions
Windows * windowsSetup();

//render functions
void render(Game * game, Windows * windows);
void drawMapInGameWindow(Game * game, Windows * windows);

//error functions
void CheckConstants();

//utilities functions
bool isNear(Position a, Position b);
bool isTooNear (Position a, Position b, int distance_limit);

//items functions
Item * genSword(int damage, int durability, char *name_sword);
Item * genPotion(int heal_points, int quantity, char * name_potion);
Item * genObject(int quantity, char skin,char * name_object, Position coordinate);

#endif
