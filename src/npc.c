#include "valley.h"

npcStruct * necomancerSetup(Map * map) // this functions creates the necromancer and set up its attributes
{
	npcStruct * npc = malloc(sizeof(npcStruct));
	
    npc->skin = 'N';

    npc->name = malloc(sizeof(char*));
    
    strcpy(npc->name, "Necro Bob");

    npc->interactions_count = 0;

    npc->quest_completed = false;

	do
	{ //generate random positions until, finds one in the bounds of the map
		npc->position.y = rand() % (map->dimensions.height - 2) + 1;
		
		npc->position.x = rand() % (map->dimensions.width - 2) + 1;
	
	} while (map->tiles[npc->position.y][npc->position.x] == '.' || 
	map->tiles[npc->position.y][npc->position.x] == '#');
	
	map->tiles[npc->position.y][npc->position.x] = npc->skin;
	map->colors[npc->position.y][npc->position.x] = MAGENTA_ON_DEFAULT;
    return npc;
}

npcStruct * wizardSetup()
{
    npcStruct * npc = malloc(sizeof(npcStruct));
    npc->skin = 'W';

    npc->name = malloc(sizeof(char*));
    strcpy(npc->name, "Strange Wizard");

    npc->interactions_count = 0;
    npc->gave_flowers = 0;

    npc->quest_completed = false;

    return npc;
}

void placeNpcInStructure(Map * map, StructureStruct * structure, npcStruct * npc)
{

    do
    {
        npc->position.y = structure->position.y + structure->dimensions.height/2;
        npc->position.x = structure->position.x + structure->dimensions.width/2;
    } while (isNear(npc->position, structure->position));

   map->tiles[npc->position.y][npc->position.x] = npc->skin;
    map->colors[npc->position.y][npc->position.x] = BLUE_ON_DEFAULT;
}


void ManageWizardInteractions (Game * game, Windows * windows)
{   
    if (game->player->inventory[2] != NULL)
    {
        mvwprintw(windows->text_window, 1, 1, "%s : HEY     THATS MY HAT", game->npc->name);
        game->npc->quest_completed = true;
    }
    else if(game->player->inventory[3] != NULL && game->player->inventory[3]->mainItems.object->quantity == FLOWER_CAPACITY_LIMIT && game->npc->interactions_count != 0 && game->npc->gave_flowers == 0)
    {
        mvwprintw(windows->text_window, 1, 1, "%s : Well, hum, thanks for the flowers. That's cool.", game->npc->name);
        game->player->inventory[3] = NULL;
        game->player->score += 10;
        game->npc->gave_flowers ++;
        return;
    }
    else if (game->player->inventory[3] != NULL && game->player->inventory[3]->mainItems.object->quantity == FLOWER_CAPACITY_LIMIT && game->npc->gave_flowers == 1)
    {
        mvwprintw(windows->text_window, 1, 1, "%s : ENOUGH OF THAT", game->npc->name);
        mvwprintw(windows->text_window, 2, 45, "%s : WHAT DO YOU THINK I AM ? A RUMINANT ?", game->npc->name);
        mvwprintw(windows->text_window, 4, 20, "%s : I JUST FINISHED EATING THE LAST ONES", game->npc->name);
        mvwprintw(windows->text_window, 5, 15, "%s : I LIVE IN A VALLEY YOU THINK IM MISSING FLOWERS", game->npc->name);
        game->npc->gave_flowers++;
    }
    else if (game->npc->interactions_count > 10)
    {
        mvwprintw(windows->text_window, 1, 1, "%s : STOP TALKING TO ME", game->npc->name);
        mvwprintw(windows->text_window, 2, 20, "%s : I NOT BE YOUR FRIEND", game->npc->name);
        mvwprintw(windows->text_window, 4, 50, "%s : or maybe if you bring me my hat", game->npc->name);
        mvwprintw(windows->text_window, 5, 3, "%s : I miss my hat..", game->npc->name);
    }
    else if(game->npc->interactions_count > 1)
    {   
        mvwprintw(windows->text_window, 1, 1, "%s : HURRY ! The dungeon is in [%d,%d].", game->npc->name, game->dungeon->position.y,game->dungeon->position.x);
        game->npc->interactions_count++;
    }
    else
    {
        mvwprintw(windows->text_window, 1, 1, "%s : HEY YOU. Go get me my magic hat you weird looking boy.", game->npc->name);
        mvwprintw(windows->text_window, 2, 1, "%s : I forgot it in this monsterful dungeon in [%d,%d].", game->npc->name, game->dungeon->position.y,game->dungeon->position.x);
        mvwprintw(windows->text_window, 3, 1, "%s : Take this sword, you're gonna need it to break the entrance.", game->npc->name);
        mvwprintw(windows->text_window, 5, 1, "'What an old and grumpy looking man' you think.");
        game->npc->interactions_count++;
    }

    if (game->npc->interactions_count == 1)
    {
        game->player->inventory[0] = genSword(5, 200, "rusty sword");
        game->player->attack = game->player->base_attack + 5;
    }
}
// The function bellow prints on the screen the lines of the necromancer npc 
void ManageNecroInteractions(Game * game, Windows * windows)
{
    if(game->necro->interactions_count == 0)
    {
	    mvwprintw(windows->text_window, 1, 1, "%s : Oh, yeah boy, u found me. Great... So, I'm the Necromancer...",game->necro->name);					
	    mvwprintw(windows->text_window, 2, 1, "%s : Listen up! I'm old, and I'm tired of chicky brats like you messing around",game->necro->name);					
	    mvwprintw(windows->text_window, 3, 1, "%s : So, let's play a little game, if you win, you win...",game->necro->name);	
        mvwprintw(windows->text_window, 4, 15, "%s : ... BUT. IF. YOU. LOSE.      I'LL KILL YOU MOUHAHAHAHAHAHHAHAHAHAHAHAHHAHAHA",game->necro->name);
        mvwprintw(windows->text_window, 5, 3, "%s : Im the necromancer.",game->necro->name);
        game->necro->interactions_count++;
    }
    else if (game->necro->interactions_count == 1)
    {
        mvwprintw(windows->text_window, 1, 1, "%s : So, what do you say weird boy ?",game->necro->name);
        mvwprintw(windows->text_window, 2, 30, "%s : Feeling  playful ?",game->necro->name);
        mvwprintw(windows->text_window, 4, 10, "'Y to accept'                            'N to deny'");

        box(windows->text_window, 0, 0);
        wrefresh(windows->text_window);
        
        char choice;
        do{
            choice = getch();
        } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

        if(choice == 'y' || choice == 'Y')
        {
            wclear(windows->text_window);
            mvwprintw(windows->text_window, 1, 1, "%s : So you accepted the challenge, mere mortal.",game->necro->name);
            mvwprintw(windows->text_window, 2, 1, "%s : Reach %d to win.",game->necro->name, WIN_SCORE);
            box(windows->text_window, 0, 0);
            wrefresh(windows->text_window);

            if(play2048(windows))
            {
                wclear(windows->text_window);
                mvwprintw(windows->text_window, 1, 1, "%s : Mere mortal, I'm impressed, your magic is very powerful.",game->necro->name);
                mvwprintw(windows->text_window, 2, 1, "%s : You won.",game->necro->name, WIN_SCORE);
                mvwprintw(windows->text_window, 3, 1, "%s : GG",game->necro->name, WIN_SCORE);
                box(windows->text_window, 0, 0);
                wrefresh(windows->text_window);
                game->necro->quest_completed=true;
                return;
            }
            else
            {
                wclear(windows->text_window);
                box(windows->text_window, 0, 0);
                mvwprintw(windows->text_window, 1, 1, "%s : oh, you losed...          ha hahaHAHAHHAHAHHAHAHHAHHAHAHAHAHAHHAHAHHAHAHAHAHAHAHAHHAHAHAHHAHAHAHAHAHHAHAHAHAHAH",game->necro->name);
                mvwprintw(windows->text_window, 2, 1, "HAHAHAHHAHAHHAHAHAHAHHAHAHYAHAHAHAHAHAHAHHAHAHAHAHAHAHAHAHAHHAHAHHAHHAHAHHAHAHAHHAAHHAHAHAAHHAHAHAHAHHAHAHAHAHAHHAHAHAHAHAH");
                mvwprintw(windows->text_window, 4, 1, "%s : ...      ..Im not going to kill you hahaha",game->necro->name);
                mvwprintw(windows->text_window, 5, 1, "%s : you're so stupid you'll certainly kill yourself chocking on some thick air",game->necro->name);
                wrefresh(windows->text_window);
                getch();
                wclear(windows->text_window);
                box(windows->text_window, 0, 0);
                mvwprintw(windows->text_window, 3, 45, "%s : Bye loser",game->necro->name);
                wrefresh(windows->text_window);
                getch();
                wclear(windows->text_window);
                box(windows->text_window, 0, 0);
                mvwprintw(windows->text_window, 1, 1, "%s : MOUHAHAHAHHAHAHAHHAHAHAHHA          necromancer     out.",game->necro->name);
                mvwprintw(windows->text_window, 3, 15, "'He disappeared'");
                wrefresh(windows->text_window);
                game->map->tiles[game->necro->position.y][game->necro->position.x] = ' ';

                box(windows->text_window, 0, 0);
                wrefresh(windows->text_window);
                wrefresh(windows->game_window);
                return;
            }
        }
        else
        {
            wclear(windows->text_window);
            mvwprintw(windows->text_window, 1, 1, "%s :              meh",game->necro->name);
            mvwprintw(windows->text_window, 2, 1, "%s :                               fair enought.",game->necro->name);
            mvwprintw(windows->text_window, 3, 15, "'He disappeared'");
            game->map->tiles[game->necro->position.y][game->necro->position.x] = ' ';
            return;
        }
    }   
}
