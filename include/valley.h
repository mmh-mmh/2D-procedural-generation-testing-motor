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

//define color pair id
#define GREEN_ON_DEFAULT 1
#define WHITE_ON_DEFAULT 2
#define RED_ON_DEFAULT 3
#define BLUE_ON_DEFAULT 4
#define YELLOW_ON_DEFAULT 5
#define MAGENTA_ON_DEFAULT 6
#define CYAN_ON_DEFAULT 7
#define BLACK_ON_WHITE 8
#define DEFAULT_ON_DEFAULT 9

#define MAP_HEIGHT 60
#define MAP_WIDTH 80

#define MAIN_WINDOW_HEIGHT 31
#define MAIN_WINDOW_WIDTH 131
#define MAIN_WINDOW_POSITION_Y 1
#define MAIN_WINDOW_POSITION_X 3

#define NOISE_DENSITY 60
#define CELLULAR_AUTOMATON_ITERATIONS 12

#define HOUSE_SIZE 6

#define HOUSE_MINIMAL_DISTANCE_FROM_PLAYER 20
#define DUNGEON_MINIMAL_DISTANCE_FROM_PLAYER 40
#define HOUSE_MINIMAL_DISTANCE_FROM_DUNGEON 30

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

typedef struct DoorStruct
{
	char type;
	Position position;
} DoorStruct;

typedef struct StructureStruct
{	
	Position position;
	Dimensions dimensions;
	DoorStruct door;
	bool chest;
} StructureStruct;

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
	int interactions_count;
} npcStruct;

typedef enum {WEAPON_TYPE, OBJECTS_TYPE,POTIONS_TYPE} itemType;

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
	} mainItems ;
	char name[256];
} Item;

typedef struct PlayerStruct
{
	Position position;
	char skin;
	int health;
    int max_health;
	Item ** inventory;
	int inventory_size;
    int score;
} PlayerStruct;

typedef struct Game
{
	Map * map;
	PlayerStruct * player;
	StructureStruct * house;
	StructureStruct * dungeon;
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
void initPlayerInventory(PlayerStruct * player);

// npc functions
npcStruct * wizardSetup();
void placeNpcInStructure(Map * map, StructureStruct * structure, npcStruct * npc);
void ManageWizardInteractions(Game * game, Windows * windows);


// mob functions
MobStruct * genMonster(Map * map, int health, int attack, char skin);

//map functions
Map * createMap();
void mapSetup(Map * map);
char ** copyMap(Map * map);
bool TryToPlaceHouseAndPlayerForMaxTrials(Game * game, int max_trials);

// Structure functions
StructureStruct * StructureSetup(int SIZE, char door, bool chest);
bool TryToPlacePlayerAndStructuresForMaxTrials(Game * game, int max_trials);
bool isStructureReachableAndNotTooNear(Map * map, PlayerStruct * Player, StructureStruct * structure, int minimal_distance);
bool isStructureStuck(Map * map, StructureStruct * structure);
void generateStructure(Map * map, StructureStruct * structure);
void generateRandomStructurePosition (Map * map, StructureStruct * structure);
bool ArePlayerHouseAndDungeonWellPlaced(Game * game);

// door functions
void PlaceDoorAtRandomSide(Map * map, StructureStruct * structure);


//procedural functions
void mapProceduralGeneration(Map * map);
void mapNoiseGeneration(Map * map, int density);
void mapApplyCellularAutomaton(Map * map, int count);
void mapFillWalls(Map * map);
void mapGroundGeneration(Map * map);
void mapFlowersGeneration(Map * map);

//pathfinding functions
bool isReachable(Map * map, Position object_a, Position object_b);

//window functions
Windows * windowsSetup();

//render functions
void render(Game * game, Windows * windows);
void printMapInWindow(Game * game, Windows * windows);
void printInventoryInWindow (PlayerStruct * player, WINDOW * inventory_window);
void printStatsInWindow(PlayerStruct * player, WINDOW * stats_window);
void refreshWindows(Windows * windows);

//error functions
void CheckConstants();

//utilities functions
bool isNear(Position a, Position b);
bool isTooNear (Position a, Position b, int distance_limit);

//item functions
Item * genSword(int damage, int durability, char *name_sword);
Item * genPotion(int heal_points, int quantity, char * name_potion);
Item * genObject(int quantity, char skin,char * name_object, Position coordinate);

#endif
