#include <DigiMouse.h>

void setup() {
  DigiMouse.begin();
}

void loop() {
  static int diff = 1;
  DigiMouse.moveX(diff);
  diff = -diff;
  DigiMouse.delay(10000);
}
