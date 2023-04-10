#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <SDL.h>
#include "SDL_ultis.h"
#include "constants.h"
#include "gallery.h"
#include "Game.h"
#include "tt_font.h"
#include "mouse_event.h"

using namespace std;

#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

int playerSelect;

Gallery* gallery = nullptr;
Text* textTexture = nullptr;
Button* buttonPlay = nullptr;
Button* buttonMode = nullptr;
Button* buttonRule = nullptr;
Button* buttonYes = nullptr;
Button* buttonNo = nullptr;

int main( int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* Font = NULL;
    SDL_Event e;
    initSDL(window , renderer , SCREEN_WIDTH , SCREEN_HEIGHT , WINDOW_TITLE);
    gallery = new Gallery(renderer);
    textTexture = new Text(renderer);

    drawIntroBackground(renderer , gallery , textTexture);
    Game game(BOARD_WIDTH , BOARD_HEIGHT);

    buttonPlay = new Button(370 , 180 , 170 , 60);
//    buttonMode = new Button(170 , 60);
//    buttonRule = new Button(170 , 60);
//    buttonYes = new Button(370 , 180 , 170 , 60);
//    buttonNo = new Button(370 , 270 , 170 , 60);

    bool quit = false;
    while( !quit )
    {
        while( SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            buttonPlay->handleEvent(&e);
            if(buttonPlay->checkMoveDown()) quit = true;
        }
    }

    auto start = CLOCK_NOW();
    renderGamePlay(renderer , game , gallery , textTexture);
    while(game.isGameRunning())
    {
        while(SDL_PollEvent(&e))    interpretEvent(e , game);
        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end - start;
        if(elapsed.count() > STEP_DELAY)
        {
            game.nextStep();
            renderGamePlay(renderer , game , gallery , textTexture);
            start = end;
        }
        SDL_Delay(150);
    }
    textTexture->free();
    TTF_CloseFont(Font);
    Font = NULL;
    TTF_Quit();
    delete textTexture;
    delete gallery;
    quitSDL(window, renderer);
	return 0;
}
