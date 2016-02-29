#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "viewport.h"

Bullet::Bullet(const std::string& name) :
  Sprite(name,  Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
),
  angle(0),
  id(0),
  eligibleToRest(false),
  strategy()
{ }


void Bullet::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  getFrame()->draw(x,y,angle);
}


void Bullet::setOrientation(int x, int y,float playerX,float playerY,float a){

 double dX = x - Gamedata::getInstance().getXmlInt("view/width")/2 ;
 double dY = y - Gamedata::getInstance().getXmlInt("view/height")/2;
 int length = sqrt((dX)*(dX) + (dY)*(dY));
 velocityX((dX)/length);
 velocityY((dY)/length);

 angle = a+270;
 
 X(playerX+50);
 Y(playerY+46);
 }
void Bullet::update(Uint32 ticks,Vector2f disp) { 
  Vector2f incr = getVelocity() *1200* static_cast<float>(ticks) * 0.001;

 setPosition(getPosition() + incr + disp);

 if(X()< Viewport::getInstance().X() || X() > (Viewport::getInstance().X()+Gamedata::getInstance().getXmlInt("view/width"))){
  eligibleToRest = true;
 }
  
 if(Y()< Viewport::getInstance().Y() || Y() > (Viewport::getInstance().Y()+Gamedata::getInstance().getXmlInt("view/height"))){
  eligibleToRest = true;
 }
}
