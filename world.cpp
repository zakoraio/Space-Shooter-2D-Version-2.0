#include <iostream>
#include "world.h"
#include "frameFactory.h"

World::World(const std::string& name, int fact) : 
  frame(FrameFactory::getInstance().getFrame(name)),
  factor(fact),
    frameWidth( frame->getWidth() ),
    frameHeight( frame->getHeight() ),
    worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{}

void World::update() {
  viewX = static_cast<int>(view.X() / factor) % frameWidth;
 // std::cout<<"viewX = "<<viewX<<std::endl;
  //.viewY = view.Y();
  viewY = static_cast<int>(view.Y() / factor) % frameHeight;
  //std::cout<<"viewY = "<<viewY<<std::endl;
}

void World::draw() const { 
  frame->draw(viewX, viewY, 0, 0); 
  frame->draw(0 , viewY , frameWidth-viewX, 0); 
  frame->draw(viewX ,0 , 0, frameHeight - viewY); 
  frame->draw(0 , 0 , frameWidth-viewX,  frameHeight - viewY); 
}

