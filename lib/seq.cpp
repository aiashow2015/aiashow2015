#include "beta-cube-library.h"
#include "seq.h"

extern Cube cube;

void Seq::setup() {
  curr_task = tasks_[curr_idx];
  curr_task->setup(millis());
}

int j = 0;
int tn = 0;

bool Seq::loop() {
  if (!curr_task) {
    return false;
  }

  long elapsed = curr_task->elapsedMillis();
  long duration = curr_task->durationMillis();
  
  if (elapsed > duration) {
    curr_task = tasks_[++curr_idx];
      if (!curr_task && repeat_) {
          curr_idx = 0;
          curr_task = tasks_[curr_idx];
      }
      
    if (curr_task) {
      curr_task->setup(millis());
        elapsed = curr_task->elapsedMillis();
        duration = curr_task->durationMillis();
    }
  }

  if (!curr_task) {
    return false;
  }

  curr_task->loop(elapsed, (double)elapsed / (double)duration);
  return true;
}
