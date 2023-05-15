#ifndef SDL_ultis__H_
#define SDL_ultis__H_

#include <iostream>
#include <SDL.h>
#include "constants.h"
#include "gallery.h"
#include "Game.h"
#include "tt_font.h"
#include "mouse_event.h"

using namespace std;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void drawIntroBackground(SDL_Renderer* renderer , Gallery* gallery , Text* textTexture , int selectMap , int selectLevel);

void drawPauseGame(SDL_Renderer* renderer , Gallery* gallery);

void renderGamePlay(SDL_Renderer* , const Game& game , Gallery* gallery , Text* textTexture , Uint32 elapsedTimeReal);

bool isContinuePlay(Button* buttonYes , Button* buttonNo , SDL_Renderer* renderer , Gallery* gallery , Text* textTextue , bool isGameOver);

void interpretEvent(SDL_Event e, Game& game);

#endif //SDL_ultis__H_
