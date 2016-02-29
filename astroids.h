#ifndef ASTROIDS__H
#define ASTROIDS__H
#include <string>
#include <vector>
#include "multisprite.h"
#include "vector2f.h"



class Astroid : public MultiSprite {
public:
  Astroid(const std::string&);
  Astroid(const Astroid&);
  virtual ~Astroid() { } 
  virtual void advanceFrame(Uint32 ticks);
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  virtual std::string getType() const { return "Astroid"; }
  int getId() { return id; }
  void setId(int id1) { id = id1; }
  bool isEligibleToRest() { return complete; }
  void readyToUse() { complete = false; }
  void setLoc(float x , float y); 
  void readyToCollect() {  complete = true; }
  static int angle;
  static float interval;
private:
int id;
bool complete;

};
#endif
