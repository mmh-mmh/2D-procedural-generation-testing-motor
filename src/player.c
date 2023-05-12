#include "valley.h"

PlayerStruct * playerSetup(int y, int x)
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->position.y = y;
	player->position.x = x;
	player->skin = '@';
	
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
	}

	return 0;
}