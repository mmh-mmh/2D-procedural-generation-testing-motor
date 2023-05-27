#include "valley.h"

void freeGame(Game *game) {
    int i;

    // Libérer les structures de la map
    for (i = 0; i < game->map->dimensions.height; i++) {
        free(game->map->tiles[i]);
        free(game->map->tiles_save[i]);
        free(game->map->colors[i]);
        free(game->map->colors_save[i]);
    }
    free(game->map->tiles);
    free(game->map->tiles_save);
    free(game->map->colors);
    free(game->map->colors_save);
    free(game->map);

    free(game->player->inventory);
    free(game->player);

    // Libérer les structures
    free(game->house);
    free(game->dungeon);

    // Libérer le mob
    free(game->mob);

    // Libérer les NPCs
    free(game->npc->name);
    free(game->npc);
    free(game->necro->name);
    free(game->necro);

    // Enfin, libérer la structure de jeu elle-même
    free(game);
}


void freeWindows(Windows *windows) {
    // Destroy all windows
    delwin(windows->main_window);
    delwin(windows->game_window);
    delwin(windows->text_window);
    delwin(windows->stats_window);
    delwin(windows->inventory_window);
    delwin(windows->loading_window);

    // Finally, free the windows structure itself
    free(windows);
}
