#ifndef POWERDEFENCEMANAGER__H
#define POWERDEFENCEMANAGER__H
#include <string>
#include <vector>
#include "multisprite.h"
#include "vector2f.h"
#include "objectPool.h"
#include "defender.h"
#include "player.h"
#include "revolvingSprite.h"
#include "bullet.h"
#include "explosion.h"
#include "multisprite.h"
#include "sprite.h"
#include "aaline.h"
#include "ioManager.h"
#include "SDL.h"
#include<cmath>
#include <SDL_mixer.h>


class PowerDefenceManager {
public:
  PowerDefenceManager();
  PowerDefenceManager(const PowerDefenceManager&);
  const PowerDefenceManager& operator=(const PowerDefenceManager& rhs);

  virtual ~PowerDefenceManager() {
  
  delete shield;
  delete health; 
  delete destroyer;
  delete blackHole;
  delete revSprite;
  Mix_FreeChunk(explode);
  Mix_CloseAudio();
 } 

  void reset();
  void initializeAll();
  void update(float x , float y,Uint32 ticks,Vector2f disp);
  void draw(SDL_Surface *screen) const ;
  void setPlayerCoords(float x, float y) { playerX = x; playerY = y; }
  
  RevolvingSprite * getDestroyer () { return revSprite; }
   
  void checkForCollisions(Player *player , ObjectPool<Bullet> * bulletObjectPool);
  ObjectPool<Explosion> * getExpObjectPool() { return &expObjectPool; }
private:

 void checkCollisionWithPlayer(Player *player, Defender *d);
 void checkCollisionWithDestroyer(Defender *d);
 void checkCollisionWithBullet(Bullet *bullet, Defender *d);
 void checkPowersAcquired(Player *player);
 void initializeDefenderH(); 
 void initializeDefenderS(); 
 void initializeDefenderD(); 
 void initializeDefenderB(); 
 void reDistribute(); 
  
ObjectPool<Explosion>  expObjectPool;
ObjectPool<Defender>  defObjectPoolH;
ObjectPool<Defender>  defObjectPoolD;
ObjectPool<Defender>  defObjectPoolB;
ObjectPool<Defender>  defObjectPoolS;




Sprite *shield;
Sprite *health;
Sprite *destroyer;
Sprite *blackHole;

RevolvingSprite *revSprite;

float playerX;
float playerY;
bool shieldT;
bool healthT;
bool destroyerT;
bool blackHoleT;

int healthCounter;
int blackHoleCounter;
int shieldCounter;

bool healthActive;
bool blackHoleActive;
bool shieldActive;
Mix_Chunk *explode;


};
#endif
