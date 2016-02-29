#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "crosshair.h"
#include "viewport.h"


CrossHair::CrossHair(const std::string& name) :
  Sprite(name,  Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
),
 x(0),
 y(0)
{ }


void CrossHair::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  getFrame()->draw(x,y);
}


void CrossHair::update(Vector2f disp) {

   X(Viewport::getInstance().X() + x + disp[0]);
   Y(Viewport::getInstance().Y() + y + disp[1]);
}
