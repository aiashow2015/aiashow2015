#ifndef FIREWORKS_H_INC
#define FIREWORKS_H_INC

#include "beta-cube-library.h"
#include "seq.h"

class Fireworks : public Task {
public:
  Fireworks(long delayMillis)
    : Task("Fireworks", delayMillis),
      rocketColor(255, 150, 100) {}

  virtual void setup(long startTimeMillis) {
    Task::setup(startTimeMillis);
    prepRocket();
  }

  virtual void loop(long elapsed, double percent);

private:
  void prepRocket();
  
  int centerX, centerY, centerZ;
  int launchX, launchZ;
  Color rocketColor;
  int r,g,b;
  int brightness=100;
  float radius=0;
  float speed;
  bool showRocket;
  bool exploded;
  float xInc, yInc, zInc;
  float rocketX, rocketY, rocketZ;
  float launchTime;
  int maxSize;
};

#endif  // FIREWORKS_H_INC
