#include <cstdlib>
#include <math.h>

#include "application.h"
#include "beta-cube-library.h"
#include "seq.h"

Cube cube;
Seq* seq;

static const Color OColor(0x9b, 0xb0, 0xff);
static const Color ODark(0x4d, 0x58, 0x7f);
static const Color BColor(0xaa, 0xbf, 0xff);
static const Color BDark(0x54, 0x5f, 0x7f);
static const Color AColor(0xca, 0xd7, 0xff);
static const Color ADark(0x64, 0x6b, 0x7f);
static const Color FColor(0xf8, 0xf7, 0xff);
static const Color FDark(0x7c, 0x7b, 0x7f);
static const Color GColor(0xff, 0xf4, 0xea);
static const Color GDark(0x7f, 0x7a, 0x75);
static const Color KColor(0xff, 0xd2, 0xa1);
static const Color KDark(0x7f, 0x68, 0x51);
static const Color MColor(0xff, 0xcc, 0x6f);
static const Color MDark(0x7f, 0x66, 0x38);

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
  static const int COLLAPSE_START_PERCENT = 90;
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

