#include <cmath>
#include "jets.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "bullet.h"
int getRandomFactor2(int max){
        int number = Gamedata::getInstance().getRandInRange(200,max);
        return number;
}

int getRandomFactorBetweenJ(int min,int max){
        int number = Gamedata::getInstance().getRandInRange(min,max);;
        number *= rand() % 2 ?  -1 : 1;
        return number;
}


Jets::Jets(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt("jets/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt("jets/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  strategy(), 
  playerX(0.0),
  playerY(0.0),
  throttleX(300),
  throttleY(throttleX),
  id(0),
  eligibleToRest(false),
  disp(Vector2f(0,0)),
  throtIncr(Vector2f(0,0))
{ 
}
Jets::Jets(const Jets& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  strategy(s.strategy),
  playerX(s.playerX),
  playerY(s.playerY),
  throttleX(s.throttleX), 
  throttleY(s.throttleY),
  id(s.id),
  eligibleToRest(s.eligibleToRest),
  disp(s.disp),
  throtIncr(s.throtIncr)
{ }

Jets& Jets::operator=(const Jets& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}



void Jets::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
   frame->draw(x,y,angle);
}

bool Jets::collidedWith(const Drawable * d) const {
	return strategy.execute((*this),*d);
}

int Jets::calculateDistance(Drawable *obj) { 
  float x,y,x1,y1;
  x = X() + frameWidth/2;
  y = Y() + frameHeight/2;
  Jets * sprite = dynamic_cast<Jets *> (obj);
  if(sprite==NULL){
  Bullet * sprite = dynamic_cast<Bullet *> (obj);
  x1 = sprite->X()+sprite->getFrame()->getWidth()/2;
  y1 = sprite->Y()+sprite->getFrame()->getHeight()/2;
  return hypot(x-x1, y-y1);
  }
  else{
  x1 = sprite->X()+sprite->getFrame()->getWidth()/2;
  y1 = sprite->Y()+sprite->getFrame()->getHeight()/2;
  return hypot(x-x1, y-y1);
  }

}

void Jets::updateVelocitiesAfterCollision() {
    velocityY( - velocityY() ) ; 
    velocityX( -velocityX() ) ;
}

void Jets::update(Uint32 ticks) { 


  int deviation = getRandomFactorBetweenJ(0,200);
  int length = sqrt((playerX+deviation - X())*(playerX+deviation-X()) + (playerY+deviation-Y())*(playerY+deviation-Y()));
  velocityX((throttleX+throtIncr[0]+disp[0])*(playerX - X())/length);
  velocityY((throttleY+throtIncr[1]+disp[1])*(playerY - Y())/length);
   int delta_x = playerX - X();
   int delta_y = playerY - Y();
   angle = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;

   Vector2f incr = getVelocity() *  static_cast<float>(ticks) * 0.001;
   if(hypot(playerX-X(),playerY-Y())<120){

      incr = getVelocity()*1.2 *  static_cast<float>(ticks) * 0.001;
   }  
   if(hypot(playerX-X(),playerY-Y())>600){

      incr = getVelocity()*8 *  static_cast<float>(ticks) * 0.001;
   }  
   incr[0]+=disp[0]/2.5;
   incr[1]+=disp[1]/2.5;
   setPosition(getPosition() + incr);


/*
  //advanceFrame(ticks);

  double radians = (1*3.1423)/180.0;   
 
  double cosA = cos(radians);
  double sinA = sin(radians);
 
  double xDiff = X()+disp[0]*.90 - playerX;
  double yDiff = Y()+disp[1]*.90 - playerY;
  
  X(cosA * (xDiff) - sinA * (yDiff) + playerX);
  Y(sinA * (xDiff) + cosA * (yDiff) + playerY);

  int length = sqrt((playerX+deviation - X())*(playerX+deviation-X()) + (playerY+deviation-Y())*(playerY+deviation-Y()));
  velocityX((throttleX)*(playerX - X())/length);
  velocityY((throttleY)*(playerY - Y())/length);
  Vector2f incr = getVelocity() *  static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);
   int delta_x = playerX - X();
   int delta_y = playerY - Y();
   angle = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;
*/
}
