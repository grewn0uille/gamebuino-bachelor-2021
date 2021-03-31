#include <Gamebuino-Meta.h>

int balle_posX = 20;
int balle_posY = 20;
int balle_speedX = 1;
int balle_speedY = 1;
int balle_taille = 4;

int raquette1_posX = 10;
int raquette1_posY = 30;

int raquette2_posX = 65;
int raquette2_posY = 30;

int raquette_hauteur = 12;
int raquette_largeur = 3;

int score1 = 0;
int score2 = 0;

void setup() {
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  balle_posX = balle_posX + balle_speedX;
  balle_posY = balle_posY + balle_speedY;

  // Si on reste appuyé vers le haut, la raquette monte
  if (gb.buttons.repeat(BUTTON_UP, 0)){
    raquette1_posY = raquette1_posY - 1;
  }
  // Si on reste appuyé vers le bas, la raquette descend
  if (gb.buttons.repeat(BUTTON_DOWN, 0)){
    raquette1_posY = raquette1_posY + 1;
  }

  // Si la balle est au dessus du centre de la raquette, la raquette va vers le bas
  if (balle_posY > raquette2_posY + raquette_hauteur / 2){
    raquette2_posY = raquette2_posY + 1;
  } else {
    // Sinon, elle va vers le haut
    raquette2_posY = raquette2_posY - 1;
  }

  // Si la balle touche le haut de l’écran, on la fait aller vers le bas
  if (balle_posY < 0){
    balle_speedY = 1;
  }
  // Si la balle touche le bas de l’écran, on la fait aller vers le haut
  if (balle_posY > gb.display.height() - balle_taille){
    balle_speedY = -1;
  }

  // Si la balle sort à droite ou à gauche de l’écran
  if ((balle_posX < 0) || (balle_posX > gb.display.width())){
    // Si elle sort à gauche, le joueur 2 gagne un point
    if (balle_posX < 0){
        score2 = score2 + 1;
    }
    // Si elle sort à droite, le joueur 1 gagne un point
    if (balle_posX > gb.display.width()){
        score1 = score1 + 1;
    }
    // On replace la balle
    balle_posX = 20;
    balle_posY = 20;
    balle_speedX = 1;
    balle_speedY = 1;
  }

  // Si la balle tape contre le bord droit de la raquette de gauche, on la renvoie vers la droite
  if ((balle_posX == raquette1_posX + raquette_largeur)
      && (balle_posY + balle_taille >= raquette1_posY)
      && (balle_posY <= raquette1_posY + raquette_hauteur)){
    balle_speedX = 1;
  }
  // Si la balle tape contre le bord gauche de la raquette de droite, on la renvoie vers la gauche
  if ((balle_posX + balle_taille == raquette2_posX)
      && (balle_posY + balle_taille >= raquette2_posY)
      && (balle_posY <= raquette2_posY + raquette_hauteur)){
    balle_speedX = -1;
  }

  // On affiche les score en haut de l’écran
  gb.display.setCursor(35, 5);
  gb.display.print(score1);
  gb.display.setCursor(42, 5);
  gb.display.print(score2);

  // On affiche la balle et les raquettes
  gb.display.fillRect(balle_posX, balle_posY, balle_taille, balle_taille);
  gb.display.fillRect(raquette1_posX, raquette1_posY, raquette_largeur, raquette_hauteur);
  gb.display.fillRect(raquette2_posX, raquette2_posY, raquette_largeur, raquette_hauteur);
}