#ifndef INVENTORYHUD__H
#define INVENTORYHUD__H


#include <iostream>
#include "ioManager.h"
#include "aaline.h"
#include "vector2f.h"

const int HUD_WIDTH_I = Gamedata::getInstance().getXmlInt("inventoryHud/width");
const int HUD_HEIGHT_I = Gamedata::getInstance().getXmlInt("inventoryHud/height");


class InventoryHud
{
    public:
    InventoryHud(SDL_Surface * screen ,int x,int y);
    void drawHUD();
    void update(int uList, int fList, int ef, int eu) { 
       useListSize = uList; freeListSize = fList; 
       expF = ef; expU = eu;    
   }
   InventoryHud(const InventoryHud&);
   InventoryHud& operator=(const InventoryHud&);
   private:

   SDL_Surface* screen;
   int startX;
   int startY;

   Vector2f fireBulletsMsgLoc;
   
   Vector2f freeListMsgLoc;
   Vector2f useListMsgLoc;
   
   Vector2f freeListLoc;
   Vector2f useListLoc;
   const std::string title;
   int freeListSize;
   int useListSize;
   int expF;
   int expU;
};

#endif
