
/* A finir une fois que les monstres sont sur l'ecran




int monsterMove(int movement_pattern)
{
	if(movement_pattern==1)
	{
		
	}
	else
	{
		clingyMonster();
	}
}
int clingyMonster(PlayerStruct * player, MobStruct * mob, char ** map,int height )
{
	if((mob->coordinates->y > player->position->y) && (mob->coordinates->y > 0) )
	{
		mob->position->y--;
	} else if((mob->coordinates->y < player->position->y) && (mob->coordinates->y < height))
	{
		mob->position->y--;
	}
}



    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        scanf("%d", &remainingTurns);
        char *directionX = "";
        char *directionY = "";
        if (thorY > lightY) {
            directionY = "N";
            thorY--;
        } else if (thorY < lightY) {
            directionY = "S";
            thorY++;
        }
        if (thorX > lightX) {
            directionX = "W";
            thorX--;
        } else if (thorX < lightX) {
            directionX = "E";
            thorX++;
        }
        printf("%s%s\n", directionY, directionX);
    }
*/

