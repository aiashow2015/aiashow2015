#include "application.h"
#include "beta-cube-library.h"
#include "cube.h"
#include "fireworks.h"
#include "seq.h"
#include "starfield.h"

Seq* seq;

Task* tasks[] = {
  // This is the sequence for Twinkle cube.
  new StarField(10600),  // approx 30 secs on Twinkle cube
  new Fireworks(39000),  // approx 60 secs on Twinkle cube

  // The nullptr means that the sequence is done.
  // Don't forget it, or it will crash!!!
  nullptr
};

void setup() {
  cube.begin();
  cube.background(black);

  seq = new Seq(tasks);
  seq->setup();
}

void loop() {
  if (!seq->loop()) {
  }
}

