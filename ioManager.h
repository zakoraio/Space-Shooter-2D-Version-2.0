#ifndef SINGLE__H
#define SINGLE__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
using std::string;
#include "gamedata.h"
#include <iomanip>

class IOManager {
public:
  static IOManager& getInstance();
  SDL_Surface * getScreen() const { return screen; }
  ~IOManager() { 
    TTF_CloseFont(font);
  }
  SDL_Surface* loadAndSet(const string& filename, bool setcolorkey) const;

  void printMessageAtF(const string& msg, Sint16 x, Sint16 y,TTF_Font * font) const;

  void printMessageAt(const string& msg, Sint16 x, Sint16 y) const;
  void printMessageCenteredAt(const string& msg, Sint16 y) const;
  void printStringAfterMessage(const string&, Uint32 x, Uint32 y) const;

  void makeFrame(int * frameCount,const string& username);

  template <typename T>
  void printMessageValueAt(const string& msg, T value, 
       Sint16 x, Sint16 y) const {
     std::stringstream strm;
     std::string message = msg;
     strm << message << value << "\0";
     message = strm.str();
     SDL_Rect dest = {x,y,0,0};
     SDL_Surface *stext = 
         TTF_RenderText_Blended(font, message.c_str(), color);
     if (stext) {
       SDL_BlitSurface( stext, NULL, screen, &dest );
       SDL_FreeSurface(stext);
     }
     else {
       throw 
       string("Couldn't allocate text sureface in printMessageValueAt");
     }
}


  void buildString(SDL_Event);
  void clearString() { inputString = ""; }
  const string& getString() const { return inputString; }

private:
  IOManager();
  IOManager(const IOManager&);
  IOManager& operator=(const IOManager&);
  const Gamedata& gdata;
  int viewWidth;
  int viewHeight;
  const unsigned MAX_STRING_SIZE;
  SDL_Surface * screen;
  TTF_Font *font;
  SDL_Color color;
  string inputString;
};
#endif
