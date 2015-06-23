#include <cstdlib>

#include "application.h"
#include "beta-cube-library.h"
#include "seq.h"

Cube cube;
Seq* seq;

static const Color OColor(0x9b, 0xb0, 0xff);
static const Color BColor(0xaa, 0xbf, 0xff);
static const Color AColor(0xca, 0xd7, 0xff);
static const Color FColor(0xf8, 0xf7, 0xff);
static const Color GColor(0xff, 0xf4, 0xea);
static const Color KColor(0xff, 0xd2, 0xa1);
static const Color MColor(0xff, 0xcc, 0x6f);

struct StarDesc {
  const Color* color;   // Color to represent this type of star.
  int percentage;       // Percentage of stars of this type (* 1000).
};

static const StarDesc ODesc = { &OColor,   1 };
static const StarDesc BDesc = { &BColor,   1 };
static const StarDesc ADesc = { &AColor,   6 };
static const StarDesc FDesc = { &FColor,  30 };
static const StarDesc GDesc = { &GColor,  76 };
static const StarDesc KDesc = { &KColor, 121 };
static const StarDesc MDesc = { &MColor, 765 };

static const StarDesc *descs[] {
  &MDesc, &KDesc, &GDesc, &FDesc, &ADesc, &BDesc, &ODesc
};

class StarField : public Task {
public:
  StarField(long delayMillis) : Task("starfield", delayMillis) {
  }

  virtual void setup(long startTimeMillis) {
    Task::setup(startTimeMillis);

    for (int i = 0; i < NUM_STARS; ++i) {
      stars[i].x = rand()%8;
      stars[i].y = rand()%8;
      stars[i].z = rand()%8;

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
  
  virtual void loop(long elapsed, double percentDone) {
    for (int i = 0; i < NUM_STARS; ++i) {
      star* s = &stars[i];
      cube.setVoxel(s->x, s->y, s->z, *s->desc->color);
    }
    cube.show();
  }
private:
  static const int NUM_STARS = 50;
  
  struct star {
    const StarDesc* desc;
    int x;
    int y;
    int z;
  };

  star stars[NUM_STARS];
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
  new StarField(600),
    // new BlueInCenter(200),
    // new BlueLine(300),
    // new BlueSquare(150),
    // new DelayTask(150),
    // new BlueCube(150),
    // new YellowLight(100),
    // new DelayTask(50),
    // new WhiteCube(300),
    // new ClearTask(10),

    // The nullptr means that the sequence is done.
    // Don't forget it, or it will crash!!!
    nullptr
};

void setup() {
  cube.begin();
  cube.background(black);
  
  seq = new Seq(tasks, true);
  seq->setup();
}

int i = 0;
int on = 0;

void loop() {
  seq->loop();
  
  if (i++ % 100 == 0) {
    on = !on;
  }

//  cube.setVoxel(7, 7, 7, on ? purple : red);
//  cube.show();
}
