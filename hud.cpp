# include "hud.h"
# include <sstream>

Hud::Hud(SDL_Surface * surface , int x , int y):
screen(surface),
startX(x),
startY(y),
pressASDWMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/pressASDWX"), Gamedata::getInstance().getXmlInt("messageCoords/pressASDWY")),
pressRotateMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/pressRotateX"), Gamedata::getInstance().getXmlInt("messageCoords/pressRotateY")),
fireBulletsMsgLoc(Gamedata::getInstance().getXmlInt("messageCoords/fireBulletsX"), Gamedata::getInstance().getXmlInt("messageCoords/fireBulletsY")),
title( Gamedata::getInstance().getXmlStr("screenTitle")),
gameStarted(false),
playerScore(0),
wave(1),
winner(false)
{
 SDL_WM_SetCaption(title.c_str(), NULL);
}


void Hud::drawHUD() {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  IOManager &io = IOManager::getInstance();
if(gameStarted){
  Draw_AALine(screen, startX, startY+HUD_HEIGHT/2,
                      startX+HUD_WIDTH,startY+HUD_HEIGHT/2,
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
   Draw_AALine(screen, startX,startY, startX+HUD_WIDTH,startY, RED);
        std::ostringstream oss;    
        oss <<" : "<< playerScore;  
        io.printMessageAt("score"+oss.str(), 10,60); 
        oss.str("");
        oss.clear(); 
        oss <<" : "<<wave;
        io.printMessageAt("wave"+oss.str(), 10,80); 
}

if(!gameStarted){
        TTF_Font * font = TTF_OpenFont(
                Gamedata::getInstance().getXmlStr("font/file").c_str(), 
                30);
io.printMessageAtF("CONTROLS",550,10,font);
io.printMessageAtF(Gamedata::getInstance().getXmlStr("pressASDW"),pressASDWMsgLoc[0],pressASDWMsgLoc[1],font);
io.printMessageAtF(Gamedata::getInstance().getXmlStr("pressRotate"),pressRotateMsgLoc[0],pressRotateMsgLoc[1],font);
io.printMessageAtF(Gamedata::getInstance().getXmlStr("fireBullets"),fireBulletsMsgLoc[0],fireBulletsMsgLoc[1],font);
TTF_CloseFont(font);
        Draw_AALine(screen, 0, 430, 
                      1500,430 , 
                      1500, 0x20,0xFF,0xFF,0x90);
  
        font = TTF_OpenFont(
                Gamedata::getInstance().getXmlStr("font/file").c_str(), 
                40);
        IOManager::getInstance().printMessageAtF("Press B to begin game", 300,300,font); 
        IOManager::getInstance().printMessageAtF("and survive 15 waves of enemies", 300,380,font); 

    TTF_CloseFont(font);
}

if(winner){

        TTF_Font * font = TTF_OpenFont(
                Gamedata::getInstance().getXmlStr("font/file").c_str(), 
                60);
io.printMessageAtF("WINNER",550,200,font);
TTF_CloseFont(font);
        Draw_AALine(screen, 0, 430, 
                      1500,430 , 
                      1500, 0x20,0xFF,0xFF,0x90);
  
        font = TTF_OpenFont(
                Gamedata::getInstance().getXmlStr("font/file").c_str(), 
                60);
        IOManager::getInstance().printMessageAtF("Press R to replay", 300,300,font); 

    TTF_CloseFont(font);
}
}

