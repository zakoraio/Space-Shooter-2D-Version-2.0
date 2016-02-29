#include "enemies.h"




  static int CXT[20] ={0,-128,-256,-384,-512,-640,640,512,384,256,128};
  static int CYT[20] ={-360,-360,-360,-360,-360,-360,-360,-360,-360,-360,-360};

  static int CYR[20] ={0,-72,-144,-216,-288,72,144,216,288};
  static int CXR[20] ={640,640,640,640,640,640,640,640,640,640};

  static int CXB[20] ={0,-128,-256,-384,-512,-640,640,512,384,256,128};
  static int CYB[20] ={360,360,360,360,360,360,360,360,360,360,360}; 

  static int CYL[20] ={0,-72,-144,-216,-288,72,144,216,288};
  static int CXL[20] ={-640,-640,-640,-640,-640,-640,-640,-640,-640,-640};

void Enemies::reset(){
wave = 1;
  std::list<Jets *>::const_iterator ptr = jetObjectPool.getInUseList()->begin();
  while(ptr!=jetObjectPool.getInUseList()->end()){
   (*ptr)->rest(); 
   ptr++;
  }
}
void Enemies::createEnemies(){

if(jetObjectPool.getInUseList()->size()<11 && wave<20){
 if(wave==1 || wave%2==0){ 
   for(unsigned int i =0;i<20;i++){
        
        Jets *j = jetObjectPool.getObjectFromPool();
        j->X(player->X()+CXT[i]);
        j->Y(player->Y()+CYT[i]);
        j->setXTh(100);
        j->setYTh(150);
   }
}

 if(wave==1 || wave%3==0){ 
   for(unsigned int i =0;i<9;i++){
        Jets *j = jetObjectPool.getObjectFromPool();
        j->X(player->X()+CXR[i]);
        j->Y(player->Y()+CYR[i]);
        j->setXTh(150);
        j->setYTh(100);
   }

}
 if(wave==1 || wave%4==0){ 
   for(unsigned int i =0;i<11;i++){
        Jets *j = jetObjectPool.getObjectFromPool();
        j->X(player->X()+CXB[i]); 
        j->Y(player->Y()+CYB[i]);
        j->setXTh(100);
        j->setYTh(150);
   }
}
 if(wave==1 || wave%5==0){ 
   for(unsigned int i =0;i<9;i++){
        Jets *j = jetObjectPool.getObjectFromPool();
        j->X(player->X()+CXL[i]); 
        j->Y(player->Y()+CYL[i]);
        j->setXTh(150);
        j->setYTh(100);

   }
}
  wave++;
}
}

void Enemies::checkForCollision(ObjectPool<Bullet> * bullets,RevolvingSprite *destroyer){

  std::list<Jets *>::const_iterator ptr = jetObjectPool.getInUseList()->begin();
  std::list<Bullet *>::const_iterator itr = bullets->getInUseList()->begin();



  while ( ptr != jetObjectPool.getInUseList()->end() ) {
    checkCollisionWithPlayer(player,(*ptr));  
    ++ptr;
  }
 
  ptr = jetObjectPool.getInUseList()->begin(); 

  while(itr!=bullets->getInUseList()->end()){
        while ( ptr != jetObjectPool.getInUseList()->end() ) {
        checkCollisionWithBullet((*itr),(*ptr));
        ++ptr;
        }  
     itr++;
  }
 
  ptr = jetObjectPool.getInUseList()->begin(); 

  if(destroyer->isActive()){
  while ( ptr != jetObjectPool.getInUseList()->end() ) {
    checkCollisionWithDestroyer(destroyer,(*ptr));  
    ++ptr;
  }
 }

}




void Enemies::checkCollisionWithDestroyer(RevolvingSprite *destroyer , Jets * ptr) {



    if(destroyer->collidesWith(ptr)){
        Explosion * explosion = expObjectPool->getObjectFromPool();
        explosion->X(destroyer->X()-destroyer->getFrame()->getWidth()/2);
        explosion->Y(destroyer->Y()-destroyer->getFrame()->getHeight()/2);
        Mix_PlayChannel( -1, explode, 0 );
        ptr->rest();
        }

}

void Enemies::checkCollisionWithPlayer(Player *player ,Jets * ptr) {



    if(player->isAlive() && player->collidesWith(ptr)){
        Explosion * explosion = expObjectPool->getObjectFromPool();
        explosion->X(player->X()-player->getFrame()->getWidth()/2);
        explosion->Y(player->Y()-player->getFrame()->getHeight()/2);
        Mix_PlayChannel( -1, explode, 0 );
        player->hit();
        ptr->rest();
        }

}


void Enemies::checkCollisionWithBullet(Bullet *itr, Jets *ptr){
                
           if(ptr->collidedWith(itr)){
             Explosion * explosion = expObjectPool->getObjectFromPool();
             explosion->X(ptr->X()-ptr->getFrame()->getWidth()-ptr->getFrame()->getWidth()/2);
             explosion->Y(ptr->Y()-ptr->getFrame()->getHeight()-ptr->getFrame()->getHeight()/2);
             Mix_PlayChannel( -1, explode, 0 );
             ptr->rest();
             itr->rest();
             player->scored();
        }
}


void Enemies::draw() const {

 std::list<Jets *>::const_iterator ptr = jetObjectPool.getInUseList()->begin();

 while(ptr!=jetObjectPool.getInUseList()->end()){
   
   (*ptr)->draw();
   ptr++;
 }

}

void Enemies::update(Uint32 ticks){ 

  bool noCollision=true;
  Vector2f throtIncr(0,0);

 std::list<Jets *>::const_iterator ptr = jetObjectPool.getInUseList()->begin();
 std::list<Jets *>::const_iterator ptr1 = jetObjectPool.getInUseList()->begin();
 
/* while(ptr!=jetObjectPool.getInUseList()->end()){
    (*ptr)->setPlayerCoordinates(player->X(),player->Y());
    (*ptr)->setPlayerDisplacement(player->getDisplacement());  
         (*ptr)->update(ticks);
  ptr++;
}*/


 while(ptr!=jetObjectPool.getInUseList()->end()){
    (*ptr)->setPlayerCoordinates(player->X(),player->Y());
    (*ptr)->setPlayerDisplacement(player->getDisplacement());  
  while(ptr1!=jetObjectPool.getInUseList()->end()){  
    (*ptr1)->setPlayerCoordinates(player->X(),player->Y());
    (*ptr1)->setPlayerDisplacement(player->getDisplacement());  
   if(((*ptr)->X()!=(*ptr1)->X() && (*ptr)->Y()!=(*ptr1)->Y()) && (*ptr1)->collidedWith((*ptr))){
     if(hypot((*ptr1)->X()-(player)->X(),(*ptr1)->Y()-(player)->Y()) > hypot((*ptr1)->X()-(player)->X(),(*ptr1)->Y()-(player)->Y()))
       { 
         throtIncr = Vector2f(10.0f,10.0f);
         (*ptr1)->setThrotIncr(throtIncr);
         (*ptr1)->update(ticks);
         throtIncr = Vector2f(-40.0f,-40.0f);
         (*ptr1)->setThrotIncr(throtIncr);
         (*ptr1)->update(ticks);
       }    
     else{
         throtIncr = Vector2f(-40.0f,-40.0f);
         (*ptr1)->setThrotIncr(throtIncr);
         (*ptr1)->update(ticks);
         throtIncr = Vector2f(10.0f,10.0f);
         (*ptr)->setThrotIncr(throtIncr);
         (*ptr)->update(ticks);
       }
     noCollision=false;
    }
   ptr1++;
 }
   if(noCollision){
         throtIncr = Vector2f(-40.0f,-40.0f);
         (*ptr)->setThrotIncr(throtIncr);
         (*ptr)->update(ticks);
  }
 ptr++;
 noCollision=true;
}
 jetObjectPool.returnObjectsToPool();
}


