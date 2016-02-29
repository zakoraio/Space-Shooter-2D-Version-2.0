#ifndef ENEMIES__H
#define ENEMIES__H
#include <string>
#include "vector2f.h"
#include "bullet.h"
#include "objectPool.h"
#include "player.h"
#include "jets.h"
#include "player.h"
#include "revolvingSprite.h"
#include "explosion.h"
#include <SDL_mixer.h>

class Enemies{
public:
  Enemies() : jetObjectPool("jets"),expObjectPool(NULL),wave(1),player(NULL),explode(NULL) { 

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    explode = Mix_LoadWAV( "sounds/boom.wav" );

  }
  virtual ~Enemies() {
     Mix_FreeChunk(explode);
     Mix_CloseAudio();
  } 
  
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  
  void reset();
  void checkForCollision(ObjectPool<Bullet> *bulletPool,RevolvingSprite *destroyer);
  void checkCollisionWithDestroyer(RevolvingSprite *destroyer, Jets *d);
  void checkCollisionWithPlayer(Player *player , Jets *d);
  void checkCollisionWithBullet(Bullet *bullet, Jets *ptr);
  void createEnemies();
  void setPlayer(Player *p) { player = p; }
  void setExplosionObjectPool(ObjectPool<Explosion> * e) { expObjectPool = e; }
  int getWave() { return wave; }
private:
 ObjectPool<Jets> jetObjectPool;
 ObjectPool<Explosion> * expObjectPool;
 int wave;
 Player *player;
 Mix_Chunk *explode;
 Enemies(const Enemies& e);
 const Enemies& operator=(const Enemies&);
};
#endif
