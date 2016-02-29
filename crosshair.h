#ifndef CROSSHAIR__H
#define CROSSHAIR__H
#include <string>
#include "drawable.h"
#include "sprite.h"
#include "vector2f.h"

class CrossHair : public Sprite {
public:
  CrossHair(const std::string&);
  CrossHair(const CrossHair& s);
  virtual ~CrossHair() {} 

  virtual void draw() const;
  virtual std::string getType()const { return "CrossHair"; }
  virtual void update(Vector2f disp);
  void setCoords(int x1 ,int y1) { x = x1; y=y1; }
private:
  int x;
  int y;
};
#endif
