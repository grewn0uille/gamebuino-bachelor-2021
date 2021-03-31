#include <Gamebuino-Meta.h>

void setup() {
  gb.begin();
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  gb.display.setColor(RED, YELLOW);

  gb.display.setFontSize(2);

  gb.display.print("hello, world\nbonjour, monde\nhola, mundo");
}