#include <cstdlib>
#include <math.h>

#include "application.h"
#include "beta-cube-library.h"
#include "seq.h"
#include "fireworks.h"

//void prepRocket();
//void fireworks_loop();

Cube cube;
Seq* seq;

static const Color OColor(0x9b, 0xb0, 0xff);
static const Color ODark(0x74, 0x84, 0xbf);
static const Color BColor(0xaa, 0xbf, 0xff);
static const Color BDark(0x7f, 0x8f, 0xbf);
static const Color AColor(0xca, 0xd7, 0xff);
static const Color ADark(0x97, 0xa1, 0xbf);
static const Color FColor(0xf8, 0xf7, 0xff);
static const Color FDark(0xba, 0xb9, 0xbf);
static const Color GColor(0xff, 0xf4, 0xea);
static const Color GDark(0xbf, 0xb7, 0xaf);
static const Color KColor(0xff, 0xd2, 0xa1);
static const Color KDark(0xbf, 0x9d, 0x7a);
static const Color MColor(0xff, 0xcc, 0x6f);
static const Color MDark(0xbf, 0x99, 0x53);

struct StarDesc {
  const Color* color;     // Color to represent this type of star.
  const Color* darkColor; // Dark twinkle color.
  int percentage;         // Percentage of stars of this type (* 1000).
};

static const StarDesc ODesc = { &OColor, &ODark,   1 };
static const StarDesc BDesc = { &BColor, &BDark,   1 };
static const StarDesc ADesc = { &AColor, &ADark,   6 };
static const StarDesc FDesc = { &FColor, &FDark,  30 };
static const StarDesc GDesc = { &GColor, &GDark,  76 };
static const StarDesc KDesc = { &KColor, &KDark, 121 };
static const StarDesc MDesc = { &MColor, &MDark, 765 };

static const StarDesc *descs[] {
  &MDesc, &KDesc, &GDesc, &FDesc, &ADesc, &BDesc, &ODesc
};

class StarField : public Task {
public:
  StarField(long delayMillis)
    : Task("starfield", delayMillis),
      collapse_percent((double)COLLAPSE_START_PERCENT / 100.0) {
  }

  virtual void setup(long startTimeMillis) {
    Task::setup(startTimeMillis);

    for (int i = 0; i < NUM_STARS; ++i) {
      stars[i].x = rand()%8;
      stars[i].y = rand()%8;
      stars[i].z = rand()%8;
      stars[i].twinkle = twinkle();

      int randType = rand()%1000;
      int len = sizeof(descs)/sizeof(*descs);
      for (int j = 0; j < len; ++j) {
        const StarDesc* desc = descs[j];
        if (randType < desc->percentage || j == len - 1) {
          stars[i].desc = desc;
          break;
        } else {
          randType -= desc->percentage;
        }
      }
    }

    cube.background(black);
  }

  bool twinkle() {
    return rand() % 100 == 1;
  }

  virtual void loop(long elapsed, double percentDone) {
    cube.background(black);

    for (int i = 0; i < NUM_STARS; ++i) {
      star* s = &stars[i];
      if (twinkle()) {
        s->twinkle = !s->twinkle;
      }
      const Color* color = s->twinkle ? s->desc->darkColor : s->desc->color;
      int x = collapse(percentDone, s->x, COLLAPSE_X);
      int y = collapse(percentDone, s->y, COLLAPSE_Y);
      int z = collapse(percentDone, s->z, COLLAPSE_Z);
      cube.setVoxel(x, y, z, *color);
    }
    cube.show();
  }

  int collapse(double percent, int val, int collapsed) {
    // Before the collapse percent, the star doesn't move.
    if (percent < collapse_percent) {
      return val;
    }

    // Expand the remaining percentage out to full domain.
    percent = (percent - collapse_percent) * 1.0 / (1.0 - collapse_percent);

    // Now interpolate.
    return val + (collapsed - val) * percent;
  }

private:
  static const int NUM_STARS = 75;
  static const int COLLAPSE_START_PERCENT = 75;
  static const int COLLAPSE_X = 0;
  static const int COLLAPSE_Y = 0;
  static const int COLLAPSE_Z = 7;

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

class Fireworks : public Task {
public:
  Fireworks(long delayMillis)
    : Task("Fireworks", delayMillis),
      rocketColor(255, 150, 100) {}

  virtual void setup(long startTimeMillis) {
    Task::setup(startTimeMillis);
    prepRocket();
  }

  virtual void loop(long elapsed, double percent) {
    cube.background(black);  //clear the cube for each frame

    if(showRocket)
      cube.shell(rocketX, rocketY, rocketZ,.05, rocketColor);

    if(exploded)
      {
        Color fireworksColor=Color(r,g,b);

        //make the color fade to black as the firework gets larger
        if(r>1)
          r-=2;
        if(g>1)
          g-=2;
        if(b>1)
          b-=2;

        cube.shell(rocketX, rocketY, rocketZ,radius, fireworksColor);
        radius+=speed;  //the sphere gets bigger
      }

    //if the rocket hasn't exploded yet, increment its position
    if(showRocket)
      {
        rocketX+=xInc;
        rocketY+=yInc;
        rocketZ+=zInc;
      }

    //if our firework gets too large, launch another rocket to another point
    if(radius>maxSize)
      prepRocket();

    if(abs(distance(centerX,centerY,centerZ,rocketX, rocketY, rocketZ)-radius)<2)
      {
        showRocket=false;
        exploded=true;
      }

    cube.show();  //send the data to the cube
  }

private:
  float distance(float x, float y, float z, float x1, float y1, float z1) {
    return(sqrt(pow(x-x1, 2) + pow(y-y1, 2) + pow(z-z1, 2)));
  }

  void prepRocket() {
    radius=0;
    centerX=rand()%8;
    centerY=rand()%8;
    centerZ=rand()%8;
    r=rand()%brightness;
    g=rand()%brightness;
    b=rand()%brightness;
    launchX=rand()%8;
    launchZ=rand()%8;
    rocketX=launchX;
    rocketY=0;
    rocketZ=launchZ;
    launchTime=15+rand()%25;
    xInc=(centerX-rocketX)/launchTime;
    yInc=(centerY-rocketY)/launchTime;
    zInc=(centerZ-rocketZ)/launchTime;
    showRocket=true;
    exploded=false;
    speed=0.20;
    maxSize=8;
  }

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


class RedLight : public Task {
public:
  RedLight(const String& name, long delayMillis) : Task(name, delayMillis) {
  }

  virtual void loop(long elapsed, double percentDone) {
    cube.setVoxel(0, 7, 7, red);
    cube.show();
  }
};

class GreenLight : public Task {
public:
  GreenLight(const String& name, long delayMillis) : Task(name, delayMillis) {
  }

  virtual void loop(long elapsed, double percentDone) {
    cube.setVoxel(0, 7, 7, green);
    cube.show();
  }
};

class YellowLight : public Task {
public:
  YellowLight(long delayMillis) : Task("YellowLight", delayMillis) {
  }

  virtual void loop(long elapsed, double percentDone) {
    cube.setVoxel(0, 7, 7, yellow);
    cube.show();
  }
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
        cube.setVoxel(3, 7, 7, blue);
        cube.show();
    }
};

class BlueLine : public Task {
public:
    BlueLine(long delayMillis) : Task("BlueLine", delayMillis) {
    }

    virtual void loop(long elapsed, double percentDone) {
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
  //  new Cylon(5000 / 5),
  //  new StarField(6000 / 5),
  //  new Fireworks(10000),
   new BlueInCenter(200),
   new BlueLine(400),
   new BlueSquare(400),
   new DelayTask(150),
   new BlueCube(300),
    // new YellowLight(100),
   new DelayTask(150),
   new WhiteCube(400),
     new ClearTask(100),

    // The nullptr means that the sequence is done.
    // Don't forget it, or it will crash!!!
    nullptr
};

void setup() {
  cube.begin();
  cube.background(black);

  seq = new Seq(tasks);
  seq->setup();

  //  prepRocket();
}

void loop() {
  if (!seq->loop()) {
    //    fireworks_loop();
  }
}

/* ------------------------------------------------------------------------ */
/* FIREWORKS STUFF */
/* ------------------------------------------------------------------------ */

// int centerX, centerY, centerZ;
// int launchX, launchZ;
// Color rocketColor(255,150,100);
// int r,g,b;
// int brightness=100;
// float radius=0;
// float speed;
// bool showRocket;
// bool exploded;
// float xInc, yInc, zInc;
// float rocketX, rocketY, rocketZ;
// float launchTime;
// int maxSize;

// void prepRocket()
// {
//   radius=0;
//   centerX=rand()%8;
//   centerY=rand()%8;
//   centerZ=rand()%8;
//   r=rand()%brightness;
//   g=rand()%brightness;
//   b=rand()%brightness;
//   launchX=rand()%8;
//   launchZ=rand()%8;
//   rocketX=launchX;
//   rocketY=0;
//   rocketZ=launchZ;
//   launchTime=15+rand()%25;
//   xInc=(centerX-rocketX)/launchTime;
//   yInc=(centerY-rocketY)/launchTime;
//   zInc=(centerZ-rocketZ)/launchTime;
//   showRocket=true;
//   exploded=false;
//   speed=0.20;
//   maxSize=8;
// }

// float distance(float x, float y, float z, float x1, float y1, float z1)
// {
//   return(sqrt(pow(x-x1,2)+pow(y-y1,2)+pow(z-z1,2)));
// }

// void fireworks_loop()
// {
//   cube.background(black);  //clear the cube for each frame

//   if(showRocket)
//     cube.shell(rocketX, rocketY, rocketZ,.05, rocketColor);

//   if(exploded)
//     {
//       Color fireworksColor=Color(r,g,b);

//       //make the color fade to black as the firework gets larger
//       if(r>1)
//         r-=2;
//       if(g>1)
//         g-=2;
//       if(b>1)
//         b-=2;

//       cube.shell(rocketX, rocketY, rocketZ,radius, fireworksColor);
//       radius+=speed;  //the sphere gets bigger
//     }

//   //if the rocket hasn't exploded yet, increment its position
//   if(showRocket)
//     {
//       rocketX+=xInc;
//       rocketY+=yInc;
//       rocketZ+=zInc;
//     }

//   //if our firework gets too large, launch another rocket to another point
//   if(radius>maxSize)
//     prepRocket();

//   if(abs(distance(centerX,centerY,centerZ,rocketX, rocketY, rocketZ)-radius)<2)
//     {
//       showRocket=false;
//       exploded=true;
//     }

//   cube.show();  //send the data to the cube
// }

