#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "revolvingSprite.h"
#include <cmath>
#include<iostream>
#include "explosion.h"
#include "astroids.h"

int Astroid::angle = 0;
float Astroid::interval=360/Gamedata::getInstance().getXmlInt("asteroidsMulti/howMany");

 
void Astroid::advanceFrame(Uint32 ticks) {
        timeSinceLastFrame += ticks;
        if (timeSinceLastFrame > frameInterval) {
            currentFrame = (currentFrame + 1) % (numberOfFrames);
            timeSinceLastFrame = 0;
        }
}


Astroid::Astroid(const std::string& name) :
  MultiSprite(name),
  id(0),
  complete(false)
{ }

Astroid::Astroid(const Astroid& e) :
  MultiSprite(e),
  id(e.id),
  complete(e.complete)
{
 }

void Astroid::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}


void Astroid::update(Uint32 ticks) {
  advanceFrame(ticks);


  double radians = angle*(3.1423/180.0);   

  angle+=1;
    
  double cosA = cos(radians);
  double sinA = sin(radians);
 
  double xDiff = 2000+200 - 200;
  double yDiff = 2000 - 2000;
  
    X(cosA * (xDiff) - sinA * (yDiff) + 2000);
    Y(sinA * (xDiff) + cosA * (yDiff) + 2000);
   if(angle<=360) angle+=interval;
   else angle = 0; 
}


void Astroid::setLoc(float x, float y) {

	
  double radians = angle*(3.1423/180.0);   

    
  double cosA = cos(radians);
  double sinA = sin(radians);
 
  double xDiff = x+200 - x;
  double yDiff = y - y;
  
    X(cosA * (xDiff) - sinA * (yDiff) + x);
    Y(sinA * (xDiff) + cosA * (yDiff) + x);
   if(angle<=360) angle+=interval;
   else angle = 0; 
  }
