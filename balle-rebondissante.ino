#include <Gamebuino-Meta.h>

int positionX = 0;
int speedX = 1;

void setup() {
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  positionX = positionX + speedX;

  gb.display.fillRect(positionX, 32, 4, 4);
}