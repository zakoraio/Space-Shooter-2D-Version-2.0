#ifndef DEFENDER__H
#define DEFENDER__H
#include <string>
#include "drawable.h"
#include "sprite.h"
#include "objectPool.h"
#include "vector2f.h"
#include "collisionStrategy.h"



class Defender : public Sprite {
public:

  static int angle;
  static float interval;
  
  Defender(const std::string&);
  virtual ~Defender() {} 
  virtual void draw() const;
  virtual std::string getType()const { return "Defender"; }
  int getId() { return id; }
  void setId(int id1) { id = id1; }
  bool isEligibleToRest() { return eligibleToRest; }
  void readyToUse() { eligibleToRest = false; } 
  void eligibleToCollect() { eligibleToRest = true; }
  void setLoc(float x , float y); 
  bool collidesWith(const Drawable* d) const {
    const Drawable *d1 = static_cast<const Drawable *>(this);
    return strategy.execute(*d1, *d);
  }

private:
  int id;
  bool eligibleToRest;
  int orientation;
  MidPointCollisionStrategy strategy;
};
#endif
