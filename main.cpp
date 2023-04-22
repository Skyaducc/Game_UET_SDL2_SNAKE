#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "SDL_ultis.h"
#include "constants.h"
#include "gallery.h"
#include "Game.h"
#include "tt_font.h"
#include "mouse_event.h"
#include "mixer.h"

using namespace std;

#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

Mix_Music* music = nullptr;
Mix_Chunk* scratch = nullptr;
Mix_Chunk* low = nullptr;
Mix_Chunk* high = nullptr;
Mix_Chunk* medium = nullptr;

int main( int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window , renderer , SCREEN_WIDTH , SCREEN_HEIGHT , WINDOW_TITLE);
    Gallery* gallery = new Gallery(renderer);
    Text* textTexture = new Text(renderer);

    drawIntroBackground(renderer , gallery , textTexture);

    Button* buttonPlay = new Button(455 , 110 , 214 , 57);
    Button* buttonExit = new Button(760 , 360 , 135 , 55);
    Button* buttonYes = new Button(350 , 250 , 50 , 20);
    Button* buttonNo = new Button(585 , 250 , 35 , 15);
//    playMusic(music , scratch , high , medium , low);

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
            buttonExit->handleEvent(&e);
            if(buttonExit->checkMoveDown())
            {
                quit = true;
                SDL_Quit();
            }
        }
    }
    while(true)
    {
        Game game(BOARD_WIDTH , BOARD_HEIGHT);
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
            SDL_Delay(200);
        }
        bool checkContinuePlay = isContinuePlay(buttonYes , buttonNo , renderer , gallery , textTexture);
        if(checkContinuePlay)
        {
//            game.playGameAgain();
            start = CLOCK_NOW();
            renderGamePlay(renderer , game , gallery , textTexture);
        }
        else break;
        cout << "out of loop" << endl;
        game.checkStatus();
    }
    textTexture->free();
    TTF_Quit();
    delete textTexture;
    delete gallery;
    quitSDL(window, renderer);
	return 0;
}
