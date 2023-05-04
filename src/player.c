#include "valley.h"

PlayerStruct * playerSetup(int y, int x)
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->position.y = y;
	player->position.x = x;
	player->skin = '@';
	player->health = 20;
	player->backpack = malloc(sizeof(Item*)*3);
	
	for(int i=0; i<3; i++)
		player->backpack[i] = malloc(sizeof(Item*));
	//start set
	player->backpack[0] = genSword(1,20,"startersword");
	
	
	return player;
}


int handlePlayerInput(PlayerStruct * player, char input, char ** map, char ** mapSave)
{
	Position posDiff;
	
	switch(input)
	{
		
		case 'z' :
		case 'Z' :
			posDiff.y = - 1;
			posDiff.x = 0;
			playerMove(player, posDiff, map, mapSave);
			break;
		case 's' :
		case 'S' :
			posDiff.y = + 1;
			posDiff.x = 0;
			playerMove(player, posDiff, map, mapSave);
			break;
		case 'q' :
		case 'Q' :
			posDiff.y = 0;
			posDiff.x = - 1;
			playerMove(player, posDiff, map, mapSave);
			break;
		case 'd' :
		case 'D' :
			posDiff.y = 0;
			posDiff.x = + 1;
			playerMove(player, posDiff, map, mapSave);
			break;
		default :
			break;
			
	}
	return 0;
}


int playerMove(PlayerStruct * player, Position posDiff, char ** map, char ** mapSave)
{

	switch (map[player->position.y + posDiff.y][player->position.x + posDiff.x])
	{
		default :
			player->position.y += posDiff.y;
			player->position.x += posDiff.x;
			break;	
		case '#':
		case '&':
			break;
		case 'O':
			handleMovable(player, posDiff, map, mapSave);
			break;
	}

	return 0;
}

int handleMovable(PlayerStruct * player, Position posDiff, char ** map, char ** mapSave)
{
	Position newMovablePosition;
	Position newPlayerPosition;

	newPlayerPosition.y = player->position.y + posDiff.y;
	newPlayerPosition.x = player->position.x + posDiff.x;

	newMovablePosition.y = newPlayerPosition.y + posDiff.y;
	newMovablePosition.x = newPlayerPosition.x + posDiff.x;

	switch(map[newMovablePosition.y][newMovablePosition.x])
	{
		default :
			map[newMovablePosition.y][newMovablePosition.x] = 'O';
			map[newPlayerPosition.y][newPlayerPosition.x] = mapSave[newPlayerPosition.y][newPlayerPosition.x];

			player->position.y = newPlayerPosition.y;
			player->position.x = newPlayerPosition.x;

			break;

		case '#':
		case '&':
			break;
	}

	return 0;
}