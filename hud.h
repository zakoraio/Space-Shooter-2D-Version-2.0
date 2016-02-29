#ifndef HUD__H
#define HUD__H


#include <iostream>
#include "ioManager.h"
#include "aaline.h"
#include "vector2f.h"

const int HUD_WIDTH = Gamedata::getInstance().getXmlInt("hud/width");
const int HUD_HEIGHT = Gamedata::getInstance().getXmlInt("hud/height");


class Hud
{
    public:
    Hud(SDL_Surface * screen ,int x,int y);
    void drawHUD();
    void setGameStarted(bool s){ gameStarted = s; }
    void setPlayerScore(int s) { playerScore = s; }
    void setWave(int w) { wave = w; }
    void won() { winner =true; }
    void resetWon() { winner = false; }
   Hud(const Hud&);
   Hud& operator=(const Hud&);
   private:

   SDL_Surface* screen;
   int startX;
   int startY;
   Vector2f pressASDWMsgLoc;
   Vector2f pressRotateMsgLoc;

   Vector2f fireBulletsMsgLoc;
   
   const std::string title;
   bool gameStarted;
   int playerScore;
   int wave;   
   bool winner;
};

#endif
