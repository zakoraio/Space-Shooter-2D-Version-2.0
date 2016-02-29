#ifndef EXPLOSION__H
#define EXPLOSION__H
#include <string>
#include <vector>
#include "multisprite.h"
#include "vector2f.h"

class Explosion : public MultiSprite {
public:
  Explosion(const std::string&);
  Explosion(const Explosion&);
  virtual ~Explosion() { } 
  virtual void advanceFrame(Uint32 ticks);
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  virtual std::string getType() const { return "Explosion"; }
  int getId() { return id; }
  void setId(int id1) { id = id1; }
  bool isEligibleToRest() { return complete; }
  void readyToUse() { complete = false; }
  bool isComplete() { return complete; }
  void completed(){ complete = true; }
  void start() { complete = false; } 
private:
bool complete;
int id;
};
#endif
