#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include"viewport.h"
#include "vector2f.h"
#include "collisionStrategy.h"
#include "health.h"

class Player : public Drawable {
public:
  Player(const std::string&);
  virtual ~Player() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks); 
  virtual void advanceFrame(Uint32 ticks);
  virtual std::string getType() const { return "Player"; }
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

  int getAngle() { return angle; }
  void setNewOrientation(int x, int y){
  if(abs(X()+frames[currentFrame]->getWidth()/2-x)>20)
  newOrientationX = x;
  if(abs(Y()+frames[currentFrame]->getHeight()/2-y)>20)
  newOrientationY = y;

  }

  bool collidesWith(const Drawable* d) const {
    const Drawable *d1 = static_cast<const Drawable *>(this);
    return strategy.execute(*d1, *d);
  }
 
  
  int getShields() { return shields; }
  int  getDestroyers() { return destroyers; }
  int getblackHoles() { return blackHoles; }
  
  

  void destroyerAcquired() { destroyers++; }
  void blackHoleAcquired() { blackHoles++; }
  void shieldAcquired() { shields++; }
  void healthAcquired() { health+=20; gotHealth=true; } 
  
  void useDestroyers() { if(destroyers > 0) destroyers--; }
  void useShields() { if(shields > 0) shields--; }
  void useblackHoles() { if(blackHoles > 0) blackHoles--; }
  
  void setKey(int c) { key = c;}
  void setrotDir(int r) { rotDir = r;}
  Vector2f getDisplacement() { return displacement;}
  bool isAlive() { return !dead; }
  void killed() { dead = true;}
  void bringToLife() { dead = false; key=0;}
  void activateShield() { shieldActive = true; }
  void deactivateShield() { shieldActive = false; }
  void hit() { 
    gotHit = true; 
    if(shieldActive) health-=1;
    else health-=10;
    }
  void toggleGodMode() { god = !god; }
  void scored() {if(h.getLength()>0){ score+=10;} }
  int getScore() { return score; }
  void reset();
  Health getHealth() { return h; }
protected:
  const std::vector<Frame *> frames;
  const std::vector<Frame *> shieldFrames;
  int oldOrientationX;
  int oldOrientationY;
  int newOrientationX;
  int newOrientationY;
 
  int worldWidth;
  int worldHeight;
  int currentFrame;  
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  int angle;
  int key;
  int rotDir;
  Vector2f displacement;
  MidPointCollisionStrategy strategy;
  bool dead;
  int shields;
  int destroyers;
  int blackHoles;
  int health;
  bool shieldActive;
  bool gotHit;
  bool gotHealth;
  int score;
  bool god;
  Health h; 
};
#endif
