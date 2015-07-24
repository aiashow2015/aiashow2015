#include "starfield.h"

#include "beta-cube-library.h"
#include "cube.h"

static const int COLLAPSE_X = 0;
static const int COLLAPSE_Y = 0;
static const int COLLAPSE_Z = 7;

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

static bool twinkle() {
  return rand() % 100 == 1;
}

void StarField::setup(long startTimeMillis) {
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

void StarField::loop(long elapsed, double percentDone) {
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

int StarField::collapse(double percent, int val, int collapsed) {
  // Before the collapse percent, the star doesn't move.
  if (percent < collapse_percent) {
    return val;
  }

  // Expand the remaining percentage out to full domain.
  percent = (percent - collapse_percent) * 1.0 / (1.0 - collapse_percent);

  // Now interpolate.
  return val + (collapsed - val) * percent;
}
