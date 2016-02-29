#include <iostream>
#include "powerDefenceManager.h"

int getRandomFactorI(int max){
        int number = Gamedata::getInstance().getRandInRange(0,max);
        number *= rand() % 2 ?  -1 : 1;
        return number;
}


int getRandomFactorBetween(int min,int max){
        int number = Gamedata::getInstance().getRandInRange(min,max);;
        number *= rand() % 2 ?  -1 : 1;
        return number;
}


PowerDefenceManager::PowerDefenceManager():
expObjectPool("explosion"),
defObjectPoolH("defender"),
defObjectPoolD("defender"),
defObjectPoolB("defender"),
defObjectPoolS("defender"),
shield(NULL),
health(NULL),
destroyer(NULL),
blackHole(NULL),
revSprite(NULL),
playerX(0),
playerY(0),
shieldT(false),
healthT(false),
destroyerT(false),
blackHoleT(false),
healthCounter(1000),
blackHoleCounter(1000),
shieldCounter(1000),
healthActive(false),
blackHoleActive(false),
shieldActive(false),
explode(NULL)
{

 Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
explode = Mix_LoadWAV( "sounds/boom.wav" );
shield = new Sprite("shield",Vector2f(0,0),Vector2f(0,0));
health = new Sprite("health",Vector2f(0,0),Vector2f(0,0));
destroyer = new Sprite("destroyer",Vector2f(0,0),Vector2f(0,0));
blackHole = new Sprite("blackHole",Vector2f(0,0),Vector2f(0,0));
revSprite = new RevolvingSprite("ast");
}


void PowerDefenceManager::initializeAll(){

initializeDefenderS();
initializeDefenderH();
initializeDefenderD();
//initializeDefenderB();

}


void PowerDefenceManager::reset(){

    std::list<Explosion *>::const_iterator ptr = expObjectPool.getInUseList()->begin();
    while((ptr!=expObjectPool.getInUseList()->end())){
     (*ptr)->completed();
     ptr++;
    }

}

void PowerDefenceManager::initializeDefenderS(){

int x = getRandomFactorBetween(1000,1500);
int y = getRandomFactorBetween(1000,1200);

int x1=0;
int y1=0;
Defender::angle = 0;

 for(int i=0;i<Gamedata::getInstance().getXmlInt("defender/howMany");i++){
   Defender *defender = defObjectPoolS.getObjectFromPool();
   defender->setRandomVelocity(0,0);
   x1 = playerX+x;
   y1 = playerY+y;
   shield->X(x1);
   shield->Y(y1);
   defender->setLoc(x1,y1);
 }
}
void PowerDefenceManager::initializeDefenderH(){

int x = getRandomFactorBetween(1501,2000);
int y = getRandomFactorBetween(1201,1600);
 
int x1=0;
int y1=0;
Defender::angle = 0;

for(int i=0;i<Gamedata::getInstance().getXmlInt("defender/howMany");i++){
   Defender *defender = defObjectPoolH.getObjectFromPool();
   defender->setRandomVelocity(0,0);
   x1 = playerX+x;
   y1 = playerY+y;
   health->X(x1);
   health->Y(y1);
   defender->setLoc(x1,y1);
 }

}
void PowerDefenceManager::initializeDefenderD(){

int x = getRandomFactorBetween(2001,2500);
int y = getRandomFactorBetween(1601,1800);
 
int x1=0;
int y1=0;
Defender::angle = 0;
for(int i=0;i<Gamedata::getInstance().getXmlInt("defender/howMany");i++){
   Defender *defender = defObjectPoolD.getObjectFromPool();
   defender->setRandomVelocity(0,0);
   x1 = playerX+x;
   y1 = playerY+y;
   destroyer->X(x1);
   destroyer->Y(y1);
   defender->setLoc(x1,y1);
 }
}
void PowerDefenceManager::initializeDefenderB(){

int x = getRandomFactorBetween(1500,2500);
int y = getRandomFactorBetween(1800,2000);
 
int x1=0;
int y1=0;
Defender::angle = 0;

for(int i=0;i<Gamedata::getInstance().getXmlInt("defender/howMany");i++){
   Defender *defender = defObjectPoolB.getObjectFromPool();
   defender->setRandomVelocity(0,0);
   x1 = playerX+x;
   y1 = playerY+y;
   blackHole->X(x1);
   blackHole->Y(y1);
   defender->setLoc(x1,y1);
 }
}


void PowerDefenceManager::reDistribute(){


  if(shieldT){
    std::list<Defender *>::const_iterator ptr = defObjectPoolS.getInUseList()->begin();
    while((ptr!=defObjectPoolS.getInUseList()->end())){
       Explosion* e = expObjectPool.getObjectFromPool();
       e->X((*ptr)->X());
       e->Y((*ptr)->Y());
        (*ptr)->eligibleToCollect();
       ptr++;
    }
    shieldT=false; 
    initializeDefenderS();
  } 
  
  if(healthT){
    std::list<Defender *>::const_iterator ptr = defObjectPoolH.getInUseList()->begin();
    while((ptr!=defObjectPoolH.getInUseList()->end())){
       Explosion* e = expObjectPool.getObjectFromPool();
       e->X((*ptr)->X());
       e->Y((*ptr)->Y());
       (*ptr)->eligibleToCollect();
       ptr++;
 
   }
    healthT=false;
    initializeDefenderH();
  } 

  if(blackHoleT){
    std::list<Defender *>::const_iterator ptr = defObjectPoolB.getInUseList()->begin();
    while((ptr!=defObjectPoolB.getInUseList()->end())){
       Explosion* e = expObjectPool.getObjectFromPool();
       e->X((*ptr)->X());
       e->Y((*ptr)->Y());
       (*ptr)->eligibleToCollect();
       ptr++;
    }
    blackHoleT=false;
    initializeDefenderB();
  } 

  if(destroyerT){
    std::list<Defender *>::const_iterator ptr = defObjectPoolD.getInUseList()->begin();
    while((ptr!=defObjectPoolD.getInUseList()->end())){
       Explosion* e = expObjectPool.getObjectFromPool();
       e->X((*ptr)->X());
       e->Y((*ptr)->Y());
       (*ptr)->eligibleToCollect();
       ptr++;
    }
    destroyerT=false;
    initializeDefenderD();
  } 
}




void PowerDefenceManager::checkForCollisions(Player *player,  ObjectPool<Bullet> * bulletObjectPool) {


  checkPowersAcquired(player);

  std::list<Defender *>::const_iterator ptr = defObjectPoolS.getInUseList()->begin();
  std::list<Bullet *>::const_iterator itr = bulletObjectPool->getInUseList()->begin();



if(!shieldActive){
  while ( ptr != defObjectPoolS.getInUseList()->end() ) {
    checkCollisionWithPlayer(player,(*ptr));  
    ++ptr;
  }
 
  player->deactivateShield();
  ptr = defObjectPoolS.getInUseList()->begin(); 

  while(itr!=bulletObjectPool->getInUseList()->end()){
  	while ( ptr != defObjectPoolS.getInUseList()->end() ) {
        checkCollisionWithBullet((*itr),(*ptr));
        ++ptr;
	}  
     itr++;
  } 

}
if(!healthActive){
  ptr = defObjectPoolH.getInUseList()->begin(); 
  itr = bulletObjectPool->getInUseList()->begin();
  while ( ptr != defObjectPoolH.getInUseList()->end() ) {
    checkCollisionWithPlayer(player,(*ptr));  
    ++ptr;
  }
 

  ptr = defObjectPoolH.getInUseList()->begin(); 

  while(itr!=bulletObjectPool->getInUseList()->end()){
  	while ( ptr != defObjectPoolH.getInUseList()->end() ) {
        checkCollisionWithBullet((*itr),(*ptr));
        ++ptr;
	}  
    itr++;
  }

} 

/*if(!blackHoleActive){
  ptr = defObjectPoolB.getInUseList()->begin(); 
  itr = bulletObjectPool->getInUseList()->begin();
  
  while ( ptr != defObjectPoolB.getInUseList()->end() ) {
    checkCollisionWithPlayer(player,(*ptr));  
    ++ptr;
  }
 

  ptr = defObjectPoolB.getInUseList()->begin(); 

  while(itr!=bulletObjectPool->getInUseList()->end()){
  	while ( ptr != defObjectPoolB.getInUseList()->end() ) {
        checkCollisionWithBullet((*itr),(*ptr));  
  ++ptr;
  } 
itr++;
}
}
*/

if(!revSprite->isActive()){
  ptr = defObjectPoolD.getInUseList()->begin(); 
  itr = bulletObjectPool->getInUseList()->begin();

  while ( ptr != defObjectPoolD.getInUseList()->end() ) {
    checkCollisionWithPlayer(player,(*ptr));  
    ++ptr;
  }
 

  ptr = defObjectPoolD.getInUseList()->begin(); 

  while(itr!=bulletObjectPool->getInUseList()->end()){
  	while ( ptr != defObjectPoolD.getInUseList()->end() ) {
        checkCollisionWithBullet((*itr),(*ptr));  
  ++ptr;
  } 
itr++;
}
}
else if(revSprite->isActive() && player->isAlive()){

  ptr = defObjectPoolB.getInUseList()->begin(); 

  while ( ptr != defObjectPoolB.getInUseList()->end() ) {
    checkCollisionWithDestroyer((*ptr));  
    ++ptr;
  }
  ptr = defObjectPoolH.getInUseList()->begin(); 

  while ( ptr != defObjectPoolH.getInUseList()->end() ) {
    checkCollisionWithDestroyer((*ptr));  
    ++ptr;
  }
  ptr = defObjectPoolS.getInUseList()->begin(); 

  while ( ptr != defObjectPoolS.getInUseList()->end() ) {
    checkCollisionWithDestroyer((*ptr));  
    ++ptr;
  }

}
reDistribute();

}


void PowerDefenceManager::checkPowersAcquired(Player *player) {

  if(player->collidesWith(health)){
        player->hit();
        player->healthAcquired();
	healthT = true;
        healthActive = true;
  }
  if(player->collidesWith(shield)){
        player->shieldAcquired();
	shieldT=true;
        shieldActive = true;
        player->activateShield();
  }
/*  if(player->collidesWith(blackHole)){
        player->blackHoleAcquired();
	blackHoleT=true;
        blackHoleActive = true;
  }*/
  if(player->collidesWith(destroyer)){
        player->destroyerAcquired();
	destroyerT=true;
        revSprite->activate();
  }
  

}


void PowerDefenceManager::checkCollisionWithPlayer(Player *player , Defender * ptr) {


   
    if(player->isAlive() && player->collidesWith(ptr)){
        Explosion * explosion = expObjectPool.getObjectFromPool();
        explosion->X(player->X()-player->getFrame()->getWidth()/2);
	explosion->Y(player->Y()-player->getFrame()->getHeight()/2);
        Mix_PlayChannel( -1, explode, 0 ); 
        player->hit();
        ptr->eligibleToCollect();
	}
 
}

void PowerDefenceManager::checkCollisionWithDestroyer(Defender * ptr) {


   
    if(ptr->collidesWith(revSprite)){
        Explosion * explosion = expObjectPool.getObjectFromPool();
        explosion->X(ptr->X()-ptr->getFrame()->getWidth()/2);
	explosion->Y(ptr->Y()-ptr->getFrame()->getHeight()/2);
        Mix_PlayChannel( -1, explode, 0 ); 
        ptr->eligibleToCollect();
	}
 
}


void PowerDefenceManager::checkCollisionWithBullet(Bullet *itr, Defender *ptr){

	   if(itr->collidesWith(ptr)){
             Explosion * explosion = expObjectPool.getObjectFromPool();
             explosion->X(ptr->X()-ptr->getFrame()->getWidth()-ptr->getFrame()->getWidth()/2);
	     explosion->Y(ptr->Y()-ptr->getFrame()->getHeight()-ptr->getFrame()->getHeight()/2);
             Mix_PlayChannel( -1, explode, 0 ); 
             ptr->eligibleToCollect();
	}  
}

void PowerDefenceManager::update(float x, float y, Uint32 ticks,Vector2f disp) {

playerX = x;
playerY = y;
expObjectPool.returnObjectsToPool();
defObjectPoolD.returnObjectsToPool();
defObjectPoolB.returnObjectsToPool();
defObjectPoolS.returnObjectsToPool();
defObjectPoolH.returnObjectsToPool();

revSprite->update(ticks,disp,x,y);


  std::list<Explosion *>::const_iterator itr = expObjectPool.getInUseList()->begin();

  while(itr!=expObjectPool.getInUseList()->end()){
   (*itr)->update(ticks);
   itr++;
  } 



  if(healthActive && healthCounter<1){
    healthActive = false;
    healthCounter = 1000;
  }
  else if(healthActive && healthCounter>0){
     healthCounter--;
  }

  if(shieldActive && shieldCounter<1){
    shieldActive = false;
    shieldCounter = 1000;
  }
  else if(shieldActive && shieldCounter>0){
     shieldCounter--;
  }

  if(blackHoleActive && blackHoleCounter<1){
    blackHoleActive = false;
    blackHoleCounter = 1000;
  }
  else if(blackHoleActive && blackHoleCounter>0){
     blackHoleCounter--;
  }

}


void PowerDefenceManager::draw(SDL_Surface *screen) const{

if(!healthActive)
health->draw();

if(!shieldActive)
shield->draw();

if(!revSprite->isActive())
destroyer->draw();

/*if(!blackHoleActive)
blackHole->draw();
*/
if(revSprite->isActive())
  revSprite->draw();




  std::list<Defender *>::const_iterator ptr = defObjectPoolS.getInUseList()->begin();

if(!shieldActive){
  while(ptr!=defObjectPoolS.getInUseList()->end()){
   (*ptr)->draw();
   ptr++;
  }  
}
 
  ptr = defObjectPoolH.getInUseList()->begin();


if(!healthActive){
  while(ptr!=defObjectPoolH.getInUseList()->end()){
   (*ptr)->draw();
   ptr++;
  }  
}


/*  ptr = defObjectPoolB.getInUseList()->begin();
if(!blackHoleActive){
  while(ptr!=defObjectPoolB.getInUseList()->end()){
   (*ptr)->draw();
   ptr++;
  }
}*/
  
  ptr = defObjectPoolD.getInUseList()->begin();
if(!revSprite->isActive()){
  while(ptr!=defObjectPoolD.getInUseList()->end()){
   (*ptr)->draw();
   ptr++;
  }

}
  std::list<Explosion *>::const_iterator itr = expObjectPool.getInUseList()->begin();

  while(itr!=expObjectPool.getInUseList()->end()){
   (*itr)->draw();
   itr++;
  } 

float startX = playerX - Viewport::getInstance().X() + 50;
float startY = playerY - Viewport::getInstance().Y() + 46;

float endX = health->X() - Viewport::getInstance().X() + 50;
float endY = health->Y() - Viewport::getInstance().Y() + 46;


if(!healthActive){

  Draw_AALine(screen, startX, startY,
                      endX,endY,
                      1.0, 0, 0xff, 0, 0xff/3);
}

if(!shieldActive){
endX = shield->X() - Viewport::getInstance().X() + 50;
endY = shield->Y() - Viewport::getInstance().Y() + 46;

  Draw_AALine(screen, startX, startY,
                      endX,endY,
                      1.0, 0, 0x90, 0xff, 0xff/3);
}
if(!revSprite->isActive()){
endX = destroyer->X() - Viewport::getInstance().X() + 50;
endY = destroyer->Y() - Viewport::getInstance().Y() + 46;

  Draw_AALine(screen, startX, startY,
                      endX,endY,
                      1.0, 0xff, 0x80, 0, 0xff/3);
}

/*if(!blackHoleActive){
endX = blackHole->X() - Viewport::getInstance().X() + 50;
endY = blackHole->Y() - Viewport::getInstance().Y() + 46;

  Draw_AALine(screen, startX, startY,
                      endX,endY,
                      1.0, 0, 0xff, 0xff, 0xff/3);
}*/
  
}
