#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "viewport.h"
#include "defender.h"


  int Defender::angle = 0;
  float Defender::interval=360/Gamedata::getInstance().getXmlInt("defender/howMany");


Defender::Defender(const std::string& name) :
  Sprite(name,  Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
),
  id(0),
  eligibleToRest(false),
  orientation(0),
  strategy()
{ }


void Defender::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  getFrame()->draw(x,y,orientation);
}



void Defender::setLoc(float x, float y) {

	
  double radians = angle*(3.1423/180.0);   

    
  double cosA = cos(radians);
  double sinA = sin(radians);
 
  double xDiff = 180;
  double yDiff = 0;
   
  double finalX = cosA * (xDiff) - sinA * (yDiff) + x;
  double finalY = sinA * (xDiff) + cosA * (yDiff) + y;
  X(finalX);
  Y(finalY);
  float delta_x = x - finalX;
  float delta_y = y - finalY;

  orientation = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;

   if(angle<=360.0) angle+=interval;
   else angle = 0; 
  }
