/*void sauvegarderPartie(const int tab[SIZE][SIZE], const Player* player, const char* nomJoueur, const char* nomCarte) {
    sauvegarderMap(tab, nomCarte);  // Sauvegarder la map dans le fichier nomCarte
    sauvegarderJoueur(player, nomJoueur);  // Sauvegarder la structure du joueur dans le fichier nomJoueur
}

void sauvegarderMap(const int tab[SIZE][SIZE], const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "wb");
    if (fichier != NULL) {
        fwrite(tab, sizeof(int), SIZE * SIZE, fichier);
        fclose(fichier);
    }
}

void sauvegarderJoueur(const Player* player, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "wb");
    if (fichier != NULL) {
        fwrite(player, sizeof(Player), 1, fichier);
        fclose(fichier);
    }
}

void chargerPartie(int tab[SIZE][SIZE], Player* player, const char* nomJoueur, const char* nomCarte) {
    chargerMap(tab, nomCarte);  // Charger la map à partir du fichier nomCarte
    chargerJoueur(player, nomJoueur);  // Charger la structure du joueur à partir du fichier nomJoueur
}


void chargerMap(int tab[SIZE][SIZE], const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "rb");
    if (fichier != NULL) {
        fread(tab, sizeof(int), SIZE * SIZE, fichier);
        fclose(fichier);
    }
}

void chargerJoueur(Player* player, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "rb");
    if (fichier != NULL) {
        fread(player, sizeof(Player), 1, fichier);
        fclose(fichier);
    }
}*/