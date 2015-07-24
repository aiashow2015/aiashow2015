#include <cstdlib>
#include <math.h>

#include "application.h"
#include "beta-cube-library.h"
#include "cube.h"
#include "seq.h"

Seq* seq;

class Cylon : public Task {
public:
  Cylon(long delayMillis) : Task("cylon", delayMillis) {
  }

  virtual void setup(long startTimeMillis) {
    Task::setup(startTimeMillis);

    currcell = 0;
    for (int i = 0; i < sizeof(cells) / sizeof(*cells); ++i) {
      cells[i].x = i;
      cells[i].intensity = 0;
    }
    lastElapsed = 0;
    cube.background(black);
  }

  virtual void loop(long elapsed, double percentDone) {
    bool stepping = false;
    if (elapsed - lastElapsed > STEP_SIZE) {
      lastElapsed = elapsed;
      stepping = true;
    }

    if (stepping) {
      if (currcell <= 0) {
        direction = 1;
      } else if (currcell >= 7) {
        direction = -1;
      }
      currcell += direction;
      if (currcell < 0) {
        currcell = 0;
      } else if (currcell > 7) {
        currcell = 7;
      }
    }

    for (int i = 0; i < sizeof(cells) / sizeof(*cells); ++i) {
      cell* c = &cells[i];
      if (stepping) {
        if (i == currcell) {
          c->intensity = 6;
        } else {
          if (c->intensity > 0) {
          c->intensity--;
          }
        }
      }
      cube.setVoxel(c->x, 5, 7, *reds[c->intensity]);
    }
    cube.show();
  }

private:
  static const int STEP_SIZE = 2;

  static const Color red0;
  static const Color red1;
  static const Color red2;
  static const Color red3;
  static const Color red4;
  static const Color red5;

  static const Color* reds[];
  struct cell {
    int x;
    int intensity;
  };
  struct cell cells[8];
  int currcell;
  int direction = 1;
  long lastElapsed;
};

const Color Cylon::red0(0x11, 0, 0);
const Color Cylon::red1(0x33, 0, 0);
const Color Cylon::red2(0x55, 0, 0);
const Color Cylon::red3(0x99, 0, 0);
const Color Cylon::red4(0xcc, 0, 0);
const Color Cylon::red5(0xff, 0, 0);
const Color* Cylon::reds[]= {
  &black, &red0, &red1, &red2, &red3, &red4, &red5
};


class ClearTask : public Task {
public:
    ClearTask(long delayMillis) : Task("ClearTask", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);
        cube.show();
    }
};

class BlueInCenter : public Task {
public:
    BlueInCenter(long delayMillis) : Task("BlueInCenter", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);

        cube.setVoxel(3, 7, 7, blue);
        cube.show();
    }
};

class BlueLine : public Task {
public:
    BlueLine(long delayMillis) : Task("BlueLine", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);

        cube.line(3, 7, 7, 3, 7 - 7 * percentDone, 7, blue);
        cube.show();
    }
};

class BlueSquare : public Task {
public:
    BlueSquare(long delayMillis) : Task("BlueSquare", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);

        int x1 = 3 - 3 * percentDone;
        int x2 = 3 + 4 * percentDone;

        cube.line(x1, 7, 7, x2, 7, 7, blue);
        cube.line(x1, 0, 7, x2, 0, 7, blue);
        cube.line(x1, 0, 7, x1, 7, 7, blue);
        cube.line(x2, 0, 7, x2, 7, 7, blue);

        cube.show();
    }
};

class BlueCube : public Task {
public:
    BlueCube(long delayMillis) : Task("BlueCube", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);

        int z1 = 7;
        int z2 = 7 - 7 * percentDone;

        cube.line(0, 7, 7, 7, 7, 7, blue);
        cube.line(0, 0, 7, 7, 0, 7, blue);
        cube.line(0, 0, 7, 0, 7, 7, blue);
        cube.line(7, 0, 7, 7, 7, 7, blue);

        cube.line(0, 7, z2, 7, 7, z2, blue);
        cube.line(0, 0, z2, 7, 0, z2, blue);
        cube.line(0, 0, z2, 0, 7, z2, blue);
        cube.line(7, 0, z2, 7, 7, z2, blue);

        cube.line(0, 0, z1, 0, 0, z2, blue);
        cube.line(0, 7, z1, 0, 7, z2, blue);
        cube.line(7, 0, z1, 7, 0, z2, blue);
        cube.line(7, 7, z1, 7, 7, z2, blue);

        cube.show();
    }
};

class WhiteCube : public Task {
public:
    WhiteCube(long delayMillis) : Task("WhiteCube", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
        cube.background(black);

        int z1 = 7;
        int z2 = 0;

        cube.line(0, 7, z1, 7, 7, z1, white);
        cube.line(0, 0, z1, 7, 0, z1, white);
        cube.line(0, 0, z1, 0, 7, z1, white);
        cube.line(7, 0, z1, 7, 7, z1, white);

        cube.line(0, 7, z2, 7, 7, z2, white);
        cube.line(0, 0, z2, 7, 0, z2, white);
        cube.line(0, 0, z2, 0, 7, z2, white);
        cube.line(7, 0, z2, 7, 7, z2, white);

        cube.line(0, 0, z1, 0, 0, z2, white);
        cube.line(0, 7, z1, 0, 7, z2, white);
        cube.line(7, 0, z1, 7, 0, z2, white);
        cube.line(7, 7, z1, 7, 7, z2, white);

        cube.show();
    }
};

Task* tasks[] = {
  // This is the sequence for the Cylon cube.
  new BlueInCenter(4000),  // approx 15 secs on Cylon cube

  new BlueLine(300),       // total of approx 10 secs
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),
  new BlueLine(300),

  new BlueSquare(300),     // total of approx 10 secs
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),
  new BlueSquare(300),

  new BlueCube(300),       // total of approx 10 secs
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),
  new BlueCube(300),

  new WhiteCube(3000),    // approx 10 secs
  new Cylon(6250),        // approx 30 secs
  
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

