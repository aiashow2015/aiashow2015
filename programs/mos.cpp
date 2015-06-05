#include "application.h"
#include "beta-cube-library.h"
#include "seq.h"

Cube cube;
Seq* seq;

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
    new BlueInCenter(2000),
    new BlueLine(300),
    new BlueSquare(150),
    new DelayTask(150),
    new BlueCube(150),
    new YellowLight(100),
    new DelayTask(50),
    new WhiteCube(300),
    new ClearTask(10),
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
