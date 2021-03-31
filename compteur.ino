#include <Gamebuino-Meta.h>

int counter = 0;

void setup() {
  gb.begin();

}

void loop() {
  while (!gb.update());
  gb.display.clear();

  if (gb.buttons.pressed(BUTTON_UP)){
    counter = counter + 1;
  }

  if (gb.buttons.pressed(BUTTON_DOWN)){
      counter = counter - 1;
  }

  gb.display.print(counter);
}