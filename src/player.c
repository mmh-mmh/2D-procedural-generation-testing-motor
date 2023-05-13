#include "valley.h"

PlayerStruct * playerSetup()
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->position.y = MAP_HEIGHT/2;
	player->position.x = MAP_WIDTH/2;
	player->skin = '@';
	
	return player;
}


Position handleInput(int input)
{
	Position position_offset;

	position_offset.y = 0;
	position_offset.x = 0;
	
	switch(input)
	{
		
		case 'z' :
		case 'Z' :
			position_offset.y = - 1;
			position_offset.x = 0;
			break;
		case 's' :
		case 'S' :
			position_offset.y = + 1;
			position_offset.x = 0;
			break;
		case 'q' :
		case 'Q' :
			position_offset.y = 0;
			position_offset.x = - 1;
			break;
		case 'd' :
		case 'D' :
			position_offset.y = 0;
			position_offset.x = + 1;
			break;
		default :
			break;
			
	}
	return position_offset;
}


void checkPosition(Position position_offset, Game * game)
{
	Position new;
	new.y = game->player->position.y + position_offset.y;
    new.x = game->player->position.x + position_offset.x;

	if (new.y >= 0 && new.y < game->map->dimensions.height && new.x >= 0 && new.x < game->map->dimensions.width)
    	{
    	switch (game->map->tiles[game->player->position.y + position_offset.y][game->player->position.x + position_offset.x])
    	{
    	    default:
				playerMove(position_offset, game);
    	        break;
     		case 'X':
    	    case 'G':
    	    case 'T':
     	       //combat(user, getMonsterAt(newPosition, level->monsters), 1);
				break;
		}
	}
}


void playerMove(Position position_offset, Game * game)
{
	Position new_position;

	new_position.y = game->player->position.y + position_offset.y;
	new_position.x = game->player->position.x + position_offset.x;



	switch (game->map->tiles[new_position.y][new_position.x])
	{
		default:
			game->player->position = new_position;
			break;
		//case '#':
		case '&':
			break;
		case 'O':
			//handleMovable();
		break;
	}

}
