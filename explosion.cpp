#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "revolvingSprite.h"
#include <cmath>
#include<iostream>
#include "explosion.h"

 
void Explosion::advanceFrame(Uint32 ticks) {
        timeSinceLastFrame += ticks;
        if (timeSinceLastFrame > frameInterval) {
            currentFrame = (currentFrame + 1) % (numberOfFrames);
            if(currentFrame == numberOfFrames-1) complete = true;
            timeSinceLastFrame = 0;
        }
}


Explosion::Explosion(const std::string& name) :
  MultiSprite(name),
  complete(false),
  id(0)
{ }

Explosion::Explosion(const Explosion& e) :
  MultiSprite(e),
  complete(e.complete),
  id(e.id)
{ }

void Explosion::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}


void Explosion::update(Uint32 ticks) {
  advanceFrame(ticks);
}
