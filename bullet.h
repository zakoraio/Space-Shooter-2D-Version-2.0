#ifndef BULLET__H
#define BULLET__H
#include <string>
#include "drawable.h"
#include "sprite.h"
#include "objectPool.h"
#include "vector2f.h"
#include "collisionStrategy.h"


class Bullet : public Sprite {
public:
  Bullet(const std::string&);
  virtual ~Bullet() {} 
  virtual void draw() const;
  virtual std::string getType()const { return "Bullet"; }
  virtual void update(Uint32 ticks,Vector2f disp);
  void setOrientation(int x,int y,float playerX ,float playerY,float angle);
  int getId() { return id; }
  void setId(int id1) { id = id1; }
  bool isEligibleToRest() { return eligibleToRest; }
  void readyToUse() { eligibleToRest = false; } 
  void rest() { eligibleToRest = true; }
  bool collidesWith(const Drawable* d) const {
    const Drawable *d1 = static_cast<const Drawable *>(this);
    return strategy.execute(*d1, *d);
  }

private:
  int angle;
  int id;
  bool eligibleToRest;
  RectangularCollisionStrategy strategy;
};
#endif
