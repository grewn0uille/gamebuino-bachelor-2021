#include <Gamebuino-Meta.h>

// Caractéristiques de la balle
const int taille_balle = 4;
int balle_posX = gb.display.width() / 2;
int balle_posY = gb.display.height() - 20;
int balle_speedX = 1;
int balle_speedY = -1;

// Caractéristiques de la raquette
const int largeur_raquette = gb.display.width() / 6;
const int hauteur_raquette = 3;
const int raquette_posY = gb.display.height() - hauteur_raquette;
int raquette_posX = gb.display.width() / 3;

// Caractéristiques des briques
const int nombre_briques = 8;
const int largeur_brique = (gb.display.width() / nombre_briques) - 2;
const int hauteur_brique = 3;
const int nombre_lignes = 5;
int ligne_briques[nombre_lignes][nombre_briques];

// Nos fonctions
void mise_a_jour_position_balle(){
  balle_posX = balle_posX + balle_speedX;
  balle_posY = balle_posY + balle_speedY;
}

void deplacement_raquette(){
  // Si on reste appuyé vers le haut, la raquette monte
  if (gb.buttons.repeat(BUTTON_LEFT, 0)){
    raquette_posX = raquette_posX - 2;
  }
  // Si on reste appuyé vers le bas, la raquette descend
  if (gb.buttons.repeat(BUTTON_RIGHT, 0)){
    raquette_posX = raquette_posX + 2;
  }
}

void rebond_balle_haut_gauche_droite(){
  // Si la balle touche le haut de l’écran, on la fait aller vers le bas
  if (balle_posY < 0){
    balle_speedY = 1;
  }
  // Si la balle touche la gauche de l’écran, on la fait aller vers la droite
  if (balle_posX < 0){
    balle_speedX = 1;
  }
  // Si la balle touche la droite de l’écran, on la fait aller vers la gauche
  if (balle_posX + taille_balle > gb.display.width()){
    balle_speedX = -1;
  }
}

void rebond_balle_raquette(){
  if (gb.collide.rectRect(balle_posX, balle_posY, taille_balle, taille_balle,
      raquette_posX, raquette_posY, largeur_raquette, hauteur_raquette)){
      balle_speedY = -1;
  }
}

void rebond_balle_briques(){
  for(int i = 0; i < nombre_lignes; i++){
    for(int j = 0; j < nombre_briques; j++){
      // On calcule la position X de la brique
      int position_x_brique = j * (largeur_brique + 2);
      int position_y_brique = i * (hauteur_brique + 2);
      if (ligne_briques[i][j] == 1){
        // Si la balle touche une brique, on met la brique à 0 et on change la direction Y de la balle
        if (gb.collide.rectRect(balle_posX, balle_posY, taille_balle, taille_balle,
            position_x_brique, position_y_brique, largeur_brique, hauteur_brique)){
          ligne_briques[i][j] = 0;
          // On met - balle_speedY
          // comme ça si on touche la brique en descente, la balle repart vers le haut
          // si on touche la brique en montant, la balle repart vers le bas
          balle_speedY = -balle_speedY;
        }
      }
    }
  }
}

void reinit_balle(){
  balle_posX = gb.display.width() / 2;
  balle_posY = gb.display.height() - 20;
  balle_speedX = 1;
  balle_speedY = -1;
}

void sortie_balle(){
  // Si la balle sort de l’écran par le bas, on la remet à sa position de départ
  if (balle_posY + taille_balle > gb.display.height()){
    reinit_balle();
  }
}

void init_briques(){
  for(int i = 0; i < nombre_lignes; i++){
    for(int j = 0; j < nombre_briques; j++){
      ligne_briques[i][j] = 1;
    }
  }
}

void affichage(){
  // On affiche les briques
  int il_y_a_encore_des_briques = false;
  for(int i = 0; i < nombre_lignes; i++){
    for(int j = 0; j < nombre_briques; j++){
      int position_x_brique = j * (largeur_brique + 2);
      int position_y_brique = i * (hauteur_brique + 2);
      // On affiche que les briques que l’on n’a pas touché. 1 = brique intacte, 0 = brique touchée
      if (ligne_briques[i][j] == 1){
        il_y_a_encore_des_briques = true;
        gb.display.fillRect(position_x_brique, position_y_brique, largeur_brique, hauteur_brique);
      }
    }
  }
  if(! il_y_a_encore_des_briques){
    gb.display.println("Bravo !");
    gb.display.println();
    gb.display.println("Appuyer sur A pour relancer");
  } else {
    // On affiche la balle et la raquette
    gb.display.fillRect(balle_posX, balle_posY, taille_balle, taille_balle);
    gb.display.fillRect(raquette_posX, raquette_posY, largeur_raquette, hauteur_raquette);
  }
}

void nouvelle_partie(){
  // Si on appuie sur A, on relance une nouvelle partie
  // On remet toutes les briques, on replace la balle et la raquette
  if(gb.buttons.repeat(BUTTON_A, 0)){
    init_briques();
    reinit_balle();
    raquette_posX = gb.display.width() / 3;
  }
}

// Setup et loop
void setup() {
  gb.begin();
  init_briques();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  mise_a_jour_position_balle();

  deplacement_raquette();

  rebond_balle_haut_gauche_droite();

  rebond_balle_briques();

  rebond_balle_raquette();

  sortie_balle();

  nouvelle_partie();

  affichage();
}