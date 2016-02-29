#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include "twowaymultisprite.h"
#include <algorithm>
Manager::~Manager() { 
delete hud;
delete player;
SDL_FreeSurface(screen);
clearSprites();
delete crossHair;
delete inventoryHud;
Mix_FreeChunk(fire);
Mix_FreeChunk(music);
Mix_CloseAudio();
}



void Manager::clearSprites(){

  std::list<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
sprites.erase(sprites.begin(),sprites.end());
enemies.reset();
 
}

int getRandomFactor(int max){
        int number = Gamedata::getInstance().getRandInRange(0,max);
        number *= rand() % 2 ?  -1 : 1;
        return number;
}


class Less{
public:
  bool operator()(Drawable* lhs, Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};



void Manager::loadSprites(){


  for(int i=0;i<Gamedata::getInstance().getXmlInt("asteroid/howMany");i++){
   Drawable *sp = new Sprite("asteroid", Vector2f(Gamedata::getInstance().getXmlInt("asteroid/srcX"),Gamedata::getInstance().getXmlInt("asteroid/srcY")), Vector2f(20+getRandomFactor(30), getRandomFactor(40)));
  sprites.push_back( 
    sp);
 }
 
 enemies.setPlayer(player); 
 enemies.createEnemies();
  
}

void Manager::reset() {
  player->reset();
  clearSprites();
  loadSprites(); 
  pdm.reset();
 // gameStarted=true;
}



Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world1("layer1", Gamedata::getInstance().getXmlInt("layer1/factor") ),
  world2("layer2", Gamedata::getInstance().getXmlInt("layer2/factor") ),
  world3("layer3", Gamedata::getInstance().getXmlInt("layer3/factor") ),
  world4("layer4", Gamedata::getInstance().getXmlInt("layer4/factor") ),
  world5("layer5", Gamedata::getInstance().getXmlInt("layer5/factor") ),
  world6("layer6", Gamedata::getInstance().getXmlInt("layer6/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("player")),
  sprites(),
  currentSprite(),
  crossHair(new CrossHair("crosshair")),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  name(  Gamedata::getInstance().getXmlStr("name") ),
  titleCoords(Gamedata::getInstance().getXmlInt("messageCoords/titleX"),Gamedata::getInstance().getXmlInt("messageCoords/titleY")),
  nameCoords(Gamedata::getInstance().getXmlInt("messageCoords/nameX"),Gamedata::getInstance().getXmlInt("messageCoords/nameY")),
  hud( new Hud(io.getScreen(), Gamedata::getInstance().getXmlInt("hud/x"),Gamedata::getInstance().getXmlInt("hud/y"))),
  inventoryHud( new InventoryHud(io.getScreen(), Gamedata::getInstance().getXmlInt("inventoryHud/x"),Gamedata::getInstance().getXmlInt("inventoryHud/y"))),
  drawHud(false),
  toggleHud(true),
  fired(false),
  markTicks(0),
  bulletObjectPool("bullet"),
  pdm(),
  enemies(),
  fire(NULL),
  music(NULL),
  gameStarted(false)
  
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);

  Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
  fire = Mix_LoadWAV( "sounds/fire.wav" );    
  music = Mix_LoadWAV( "sounds/Electric.wav" );    

  loadSprites();
   
  currentSprite = player;

  pdm.setPlayerCoords(player->X(),player->Y());
  pdm.initializeAll();
  enemies.setExplosionObjectPool(pdm.getExpObjectPool());
  viewport.setObjectToTrack(currentSprite);
}

void Manager::draw() const {
  world6.draw();
  world5.draw();
  world4.draw();
  world3.draw();

  world2.draw();

  world1.draw();
 if(drawHud || toggleHud){
  clock.draw();
  inventoryHud->drawHUD();
  hud->drawHUD();
}



if(gameStarted){ 
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
  
 



  std::list<Bullet *>::const_iterator itr = bulletObjectPool.getInUseList()->begin();
  while(itr!=bulletObjectPool.getInUseList()->end()){
  (*itr)->draw();
  ++itr;
  } 
  
  crossHair->draw();
  IOManager::getInstance().
    printMessageAt(title, titleCoords[0], titleCoords[1]);
  IOManager::getInstance().
    printMessageAt(name,nameCoords[0], nameCoords[1]);

  pdm.draw(screen);
  
  //if(player->isAlive()){
    player->draw();
 // }

  enemies.draw();
}
  viewport.draw();

  SDL_Flip(screen);

}

void Manager::update() {
  if(!gameStarted) reset();
  if(gameStarted){

  hud->resetWon(); 
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();

  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
  
  if ( makeVideo && frameCount < frameMax ) {
    io.makeFrame(&frameCount,username);
  }
  if(player->getHealth().getLength()>0){
  enemies.setPlayer(player);
  enemies.createEnemies();
}

  enemies.update(ticks);
 
  std::list<Bullet *>::const_iterator itr = bulletObjectPool.getInUseList()->begin();
  while(itr!=bulletObjectPool.getInUseList()->end()){
  (*itr)->update(ticks,player->getDisplacement());
  ++itr;
  }

  enemies.checkForCollision(&bulletObjectPool , pdm.getDestroyer());
  if(player->isAlive()){
  player->update(ticks);
 }
  bulletObjectPool.returnObjectsToPool();
  pdm.checkForCollisions(player,&bulletObjectPool);
  pdm.update(player->X(),player->Y(),ticks,player->getDisplacement());
   
  hud->setPlayerScore(player->getScore());
  hud->setWave(enemies.getWave()); 
  inventoryHud->update(bulletObjectPool.getInUseList()->size(),bulletObjectPool.getFreeList()->size(),pdm.getExpObjectPool()->getFreeList()->size(),pdm.getExpObjectPool()->getInUseList()->size());
  world1.update();
  world2.update();
  world3.update();
  world4.update();
  world5.update();
  world6.update();
  crossHair->update(player->getDisplacement());
  if(enemies.getWave()==15){
   gameStarted=false;
   hud->won();
   drawHud = true;
   toggleHud = true;
 //  reset();
  }  
  viewport.update(); // always update viewport last
 }
}


void Manager::play() {
  SDL_Event event;
 
 bool done = false;
  if(gameStarted){
  clock.start();
  reset();
  }
 int startT,now;
  drawHud=true; 
    int x_coordinate = 0, y_coordinate = 0;
  startT=clock.getSeconds();
 SDL_ShowCursor(SDL_DISABLE);
 Mix_PlayChannel( -1, music, 0 );

 while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
     fired = false;
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
       
        if ( keystate[SDLK_r] ) {
           reset();
           gameStarted=true;
        }
        if ( keystate[SDLK_g] ) {
           player->toggleGodMode();
        }
        if ( keystate[SDLK_b] ) {
            hud->setGameStarted(true);
            gameStarted = true;
        }

        if ( keystate[SDLK_F1] ) {
           toggleHud = !toggleHud;
        }
        if(player->isAlive()){
          if(keystate[SDLK_RIGHT])  player->setrotDir(-1); 
          if(keystate[SDLK_LEFT])  player->setrotDir(1); 

          if(keystate[SDLK_a])  player->setKey(1);  
          else if(keystate[SDLK_s])  player->setKey(2);
          else if(keystate[SDLK_d])  player->setKey(3); 
          else if(keystate[SDLK_w])  player->setKey(4); 
          if(keystate[SDLK_a] && keystate[SDLK_s]) player->setKey(5); 
          else if(keystate[SDLK_a] && keystate[SDLK_w]) player->setKey(6); 
          else if(keystate[SDLK_w] && keystate[SDLK_d]) player->setKey(7); 
          else if(keystate[SDLK_s] && keystate[SDLK_d]) player->setKey(8); 
          else if(keystate[SDLK_s] && keystate[SDLK_d]) player->setKey(8); 
          else if(keystate[SDLK_s] && keystate[SDLK_w]) player->setKey(0);
          else if(keystate[SDLK_a] && keystate[SDLK_d]) player->setKey(0); 
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
      }

     else if(event.type == SDL_KEYUP && player->isAlive()){
        player->setKey(0);
        player->setrotDir(0);
        if(keystate[SDLK_a]) { player->setKey(1);}
        else if(keystate[SDLK_s]) { player->setKey(2);}
        else if(keystate[SDLK_d]) { player->setKey(3);}
        else if(keystate[SDLK_w]) { player->setKey(4);}
        
        if(keystate[SDLK_RIGHT])  player->setrotDir(-1); 
        if(keystate[SDLK_LEFT])  player->setrotDir(1); 
        }

      else if( event.type == SDL_MOUSEMOTION && player->isAlive() ) {
               SDL_GetMouseState(&x_coordinate, &y_coordinate);
               player->setNewOrientation(x_coordinate,y_coordinate);
               crossHair->setCoords(x_coordinate,y_coordinate);
         }

       if( event.type == SDL_MOUSEBUTTONDOWN)
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
                if(!fired && player->getHealth().getLength()>0){
		        Mix_PlayChannel( -1, fire, 0 );
                        Bullet * bullet = bulletObjectPool.getObjectFromPool();
                        bullet->X(player->X());
                        bullet->Y(player->Y());
                        bullet->setOrientation(event.button.x,event.button.y,player->X(),player->Y(),player->getAngle());
                        fired = true;
                }
        }
    }


    }


    draw();
    update();
    now = clock.getSeconds();
    if(now-startT>2&&now<5){
      drawHud= false;
     
    }
  }
}
