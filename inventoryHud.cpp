# include <sstream>
#include "inventoryHud.h"


InventoryHud::InventoryHud(SDL_Surface * surface , int x , int y):
screen(surface),
startX(x),
startY(y),
fireBulletsMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/fireBulletsX"), Gamedata::getInstance().getXmlInt("messageCoords/fireBulletsY")),
freeListMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/freeListMsgX"), Gamedata::getInstance().getXmlInt("messageCoords/freeListMsgY")),
useListMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/useListMsgX"), Gamedata::getInstance().getXmlInt("messageCoords/useListMsgY")),
freeListLoc(Gamedata::getInstance().getXmlInt("messageCoords/freeListX"), Gamedata::getInstance().getXmlInt("messageCoords/freeListY")),
useListLoc(Gamedata::getInstance().getXmlInt("messageCoords/useListX"), Gamedata::getInstance().getXmlInt("messageCoords/useListY")),
title( Gamedata::getInstance().getXmlStr("screenTitle")),
freeListSize(0),
useListSize(0),
expF(0),
expU(0)
{
 SDL_WM_SetCaption(title.c_str(), NULL);
}


void InventoryHud::drawHUD() {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, startX, startY+HUD_HEIGHT_I/2,
                      startX+HUD_WIDTH_I,startY+HUD_HEIGHT_I/2,
                      HUD_HEIGHT_I, 0xff, 0xff, 0xff, 0xff/2);
   Draw_AALine(screen, startX,startY, startX+HUD_WIDTH_I,startY, RED);
  IOManager &io = IOManager::getInstance();

io.printMessageAt(Gamedata::getInstance().getXmlStr("freeListMsg"),freeListMsgLoc[0],freeListMsgLoc[1]);
io.printMessageAt(Gamedata::getInstance().getXmlStr("useListMsg"),useListMsgLoc[0],useListMsgLoc[1]);

std::stringstream strm;
strm << freeListSize;

io.printMessageAt(strm.str(),freeListLoc[0],freeListLoc[1]);

strm.str("");
strm.clear();

strm << useListSize;

io.printMessageAt(strm.str(),useListLoc[0],useListLoc[1]);
  
io.printMessageAt("Explosion Free : ",1100,10);
io.printMessageAt("Explosion InUse: ",1100,30);

strm.str("");
strm.clear();

strm <<expF;

io.printMessageAt(strm.str(),1230,10);
strm.str("");
strm.clear();

strm <<expU;

io.printMessageAt(strm.str(),1230,30);
}

