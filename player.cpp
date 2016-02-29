#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <cmath>
#include "player.h"
void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
	    currentFrame = (currentFrame + 1) % (numberOfFrames/2);
	    timeSinceLastFrame = 0;
	}
}

Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))),
  frames( FrameFactory::getInstance().getFrames(name) ),
  shieldFrames( FrameFactory::getInstance().getFrames("shieldedPlayer")),
  oldOrientationX(0),
  oldOrientationY(0),
  newOrientationX(0),
  newOrientationY(0),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  angle(0),
  key( 0 ),
  rotDir(0),
  displacement(Vector2f(0,0)),
  strategy(),
  dead(false),
  shields(0),
  destroyers(0),
  blackHoles(0),
  health(100), 
  shieldActive(false),
  gotHit(false),
  gotHealth(false),
  score(0),
  god(false),
  h()
{ }


void Player::reset(){
setPosition(
           Vector2f(Gamedata::getInstance().getXmlInt("player/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt("player/startLoc/y")));
health = 100;
score =  0;
h.reset();
}

void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(shieldActive)
  shieldFrames[currentFrame]->draw(x, y,angle);
  else
  frames[currentFrame]->draw(x, y,angle);
  h.draw();
}



void Player::update(Uint32 ticks) {

  int delta_x = newOrientationX - Gamedata::getInstance().getXmlInt("view/width")/2;
  int delta_y = newOrientationY - Gamedata::getInstance().getXmlInt("view/height")/2 ;
  angle = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;


  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;

  displacement[0] = incr[0];
  displacement[1] = incr[1];

  setPosition(getPosition() + incr);


 if(gotHit && !god){
  
  h.update(shieldActive,gotHealth);
  gotHit = false;
  gotHealth=false;
  h.setScore(score);  
  }
if(h.getLength()>0){
  if(key==1) { velocityY(0.0);velocityX(-500.0);}
  else if(key == 2 ) { velocityY(500.0);velocityX(0.0); }
  else if(key == 3) { velocityY(0.0);velocityX(500.0);}
  else if(key == 4) { velocityY(-500.0);velocityX(0.0);}
  else if(key == 5){ velocityY(500.0);velocityX(-500.0);}
  else if(key == 6){ velocityY(-500.0);velocityX(-500.0);}
  else if(key == 7){ velocityY(-500.0);velocityX(500.0);}
  else if(key == 8){ velocityY(500.0);velocityX(500.0);}
  
  else if(key == 0){
    if(velocityX()>0) 
      velocityX(velocityX()-50.0);
    else if(velocityX()< 0) 
      velocityX(velocityX()+50.0);
    else
      velocityX(0.0); 
 
    if(velocityY()>0) 
      velocityY(velocityY()-50.0); 
    else if(velocityY() < 0.0) 
      velocityY(velocityY()+50.0);
    else velocityY(0.0);
   }
   
  if ( Y() < Gamedata::getInstance().getXmlInt("view/height")/2) { Y(Gamedata::getInstance().getXmlInt("view/height")/2);}
  if ( Y() > worldHeight-Gamedata::getInstance().getXmlInt("view/height")/2-frameHeight) { Y(worldHeight-Gamedata::getInstance().getXmlInt("view/height")/2-frameHeight); }
  if ( X() < Gamedata::getInstance().getXmlInt("view/width")/2) {X(Gamedata::getInstance().getXmlInt("view/width")/2);}
  if ( X() > worldWidth-Gamedata::getInstance().getXmlInt("view/width")/2-frameWidth) { X(worldWidth-Gamedata::getInstance().getXmlInt("view/width")/2-frameWidth); } 
}
}
