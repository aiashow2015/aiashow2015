#ifndef STARFIELD_H_INC
#define STARFIELD_H_INC

#include "seq.h"

class StarDesc;

class StarField : public Task {
public:
  StarField(long delayMillis)
    : Task("starfield", delayMillis),
      collapse_percent((double)COLLAPSE_START_PERCENT / 100.0) {
  }

  virtual void setup(long startTimeMillis);
  virtual void loop(long elapsed, double percentDone);

private:
  static const int NUM_STARS = 75;
  static const int COLLAPSE_START_PERCENT = 90;

  int collapse(double percent, int val, int collapsed);

  struct star {
    const StarDesc* desc;
    int x;
    int y;
    int z;
    int twinkle;
  };

  star stars[NUM_STARS];
  double collapse_percent;
};

#endif  // STARFIELD_H_INC
