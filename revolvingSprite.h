#ifndef REVOLVINGSPRITE__H
#define REVOLVINGSPRITE__H
#include <string>
#include <vector>
#include "multisprite.h"
#include "vector2f.h"
#include "collisionStrategy.h"

class RevolvingSprite : public MultiSprite {
public:
  RevolvingSprite(const std::string&);
  RevolvingSprite(const RevolvingSprite&);
  virtual ~RevolvingSprite() { } 
  virtual void update(Uint32 ticks, Vector2f disp, float cX, float cY);
  virtual void draw() const;
  virtual std::string getType() const { return "RevolvingSprite"; }
  void activate() { active = true; }
  void deactivate() { active = false; }
  bool isActive() { return active; }
  bool collidesWith(const Drawable* d) const {
    const Drawable *d1 = static_cast<const Drawable *>(this);
    return strategy.execute(*d1, *d);
  }
private:
  bool active;
  double angle;
  double rotationCount;
  PerPixelCollisionStrategy strategy;
};
#endif
