#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "hud.h"
#include "revolvingSprite.h"
#include "crosshair.h"
#include "objectPool.h"
#include "bullet.h"
#include "explosion.h"
#include "astroids.h"
#include "powerDefenceManager.h"
#include "inventoryHud.h"
#include "enemies.h"
#include <SDL_mixer.h>


class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
   IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World world1;
  World world2;
  World world3;
  World world4;
  World world5;
  World world6;
  Viewport& viewport;
 
  Player* player;
  std::list<Drawable*> sprites;
  Drawable* currentSprite;

  CrossHair *crossHair;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
  std::string name; 
  Vector2f titleCoords;
  Vector2f nameCoords;

  Hud * hud;
  InventoryHud * inventoryHud;
  bool drawHud;
  bool toggleHud;
  bool fired; 
  long markTicks;
  ObjectPool<Bullet> bulletObjectPool;
  PowerDefenceManager pdm; 
  Enemies enemies;
  Mix_Chunk *fire;
  Mix_Chunk *music;
  bool gameStarted; 
  
  void draw() const;
  void update();
  void reset();
  void clearSprites();
  void loadSprites();
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
