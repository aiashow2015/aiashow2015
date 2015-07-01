#ifndef SEQ_H_INC
#define SEQ_H_INC

#include "application.h"

#if TARGET_OS_MAC
#else
#define logit(a, b) 
#endif

class Seq;

class Task {

 protected:
 Task(const String &name, long durationMillis) : name_(name), durationMillis_(durationMillis) {};

  // Subclasses should feel free to override this method, but they MUST call the
  // method in the superclass.
  virtual void setup(long startTimeMillis) {
      startTimeMillis_ = startTimeMillis;
      logit(name_, startTimeMillis);
  }
  virtual void loopInternal() {
  }

  // Subclasses perform their task by overriding "loop()".
  virtual void loop(long elapsed, double percentDone) = 0;

  long startTimeMillis() { return startTimeMillis_; }
  long elapsedMillis() { return millis() - startTimeMillis_; };
  long durationMillis() { return durationMillis_; }

 private:
  // Disallow copy ctors
  Task(const Task&);
  void operator=(const Task&);

  String name_;
  long durationMillis_;
  long startTimeMillis_;

  friend Seq;
};

class Seq {
public:
    Seq(Task** tasks) : tasks_(tasks), curr_idx(0), repeat_(true) {}
    Seq(Task** tasks, bool repeat) : tasks_(tasks), curr_idx(0), repeat_(repeat) {}

  void setup();
  // returns true if the loop is still running.
  bool loop();

 private:
  // Disallow copy ctors
  Seq(const Seq&);
  void operator=(const Seq&);

  Task** tasks_;
  Task* curr_task;
  int curr_idx;
    
    bool repeat_;
};

class DelayTask : public Task {
 public:
  DelayTask(long delayMillis) : Task("Delay", delayMillis) {};

  virtual void loop(long elapsed, double percentDone) { };

 private:
  DelayTask(const DelayTask&);
  void operator=(const DelayTask&);
};


#endif  // SEQ_H_INC
