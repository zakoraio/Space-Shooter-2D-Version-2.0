#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "revolvingSprite.h"
#include <cmath>
#include<iostream>


RevolvingSprite::RevolvingSprite( const std::string& name) :
  MultiSprite(name),
  active(false),
  angle(10.0),
  rotationCount(1000),
  strategy()
{ }


void RevolvingSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}


void RevolvingSprite::update(Uint32 ticks, Vector2f disp, float cX, float cY) {
  advanceFrame(ticks);

  double radians = (angle*3.1423)/180.0;   
 
  double cosA = cos(radians);
  double sinA = sin(radians);
 
  double xDiff = X()+disp[0] - cX;
  double yDiff = Y()+disp[1] - cY;
  
  X(cosA * (xDiff) - sinA * (yDiff) + cX);
  Y(sinA * (xDiff) + cosA * (yDiff) + cY);

  if(active && rotationCount<1){
    active = false;
    rotationCount = 1000;
  }
  else if(active && rotationCount>0){
     rotationCount--;
  }
  

}
