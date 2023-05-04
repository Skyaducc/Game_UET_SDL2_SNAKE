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

int main( int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window , renderer , SCREEN_WIDTH , SCREEN_HEIGHT , WINDOW_TITLE);
    Gallery* gallery = new Gallery(renderer);
    Text* textTexture = new Text(renderer);

    Button* buttonPlay = new Button(455 , 110 , 214 , 57);
    Button* buttonExit = new Button(760 , 360 , 135 , 55);
    Button* buttonYes = new Button(350 , 250 , 50 , 20);
    Button* buttonNo = new Button(585 , 250 , 35 , 15);
    Button* buttonPause = new Button(10 , 10 , 50 , 50);
    Button* buttonMap = new Button(100 , 280 , 200 , 150);
    Button* buttonMapForest = new Button(180 , 120 , 170 , 90);
    Button* buttonMapField = new Button(440 , 40 , 130 , 80);
    Button* buttonMapIce = new Button(540 , 160 , 150 , 90);
    Button* buttonMapVolcano = new Button(470 , 330 , 140 , 80);

    bool exit = false;
    bool quit = false;
    int selectMap = 1;
    loadMusic("sound_and_music/intro_sound_track.wav");
    while( !quit )
    {
        drawIntroBackground(renderer , gallery , textTexture , selectMap);
        while( SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            buttonPlay->handleEvent(&e);
            if(buttonPlay->checkMoveDown())
            {
                loadWAV("sound_and_music/click_button.wav");
                quit = true;
            }
            buttonExit->handleEvent(&e);
            if(buttonExit->checkMoveDown())
            {
                loadWAV("sound_and_music/click_button.wav");
                quit = true;
                exit = true;
                SDL_Quit();
            }
            buttonMap->handleEvent(&e);
            if(buttonMap->checkMoveDown())
            {
                loadWAV("sound_and_music/click_button.wav");
                bool quitMap = false;
                while( !quitMap )
                {
                    SDL_RenderCopy(renderer , gallery->getImage(PIC_MAPS) , NULL , NULL);
                    SDL_RenderPresent(renderer);
                    while(SDL_PollEvent(&e) != 0)
                    {
                        if(e.type == SDL_QUIT)  quitMap = true;
                        buttonMapForest->handleEvent(&e);
                        if(buttonMapForest->checkMoveDown())
                        {
                            loadWAV("sound_and_music/click_button.wav");
                            quitMap = true;
                            selectMap = 0;
                        }
                        buttonMapField->handleEvent(&e);
                        if(buttonMapField->checkMoveDown())
                        {
                            loadWAV("sound_and_music/click_button.wav");
                            quitMap = true;
                            selectMap = 1;
                        }
                        buttonMapIce->handleEvent(&e);
                        if(buttonMapIce->checkMoveDown())
                        {
                            loadWAV("sound_and_music/click_button.wav");
                            quitMap = true;
                            selectMap = 2;
                        }
                        buttonMapVolcano->handleEvent(&e);
                        if(buttonMapVolcano->checkMoveDown())
                        {
                            loadWAV("sound_and_music/click_button.wav");
                            quitMap = true;
                            selectMap = 3;
                        }
                    }
                }
            }
        }
    }
    Mix_HaltMusic();
    if(exit)    return 0;
    while(true)
    {
        Game game(BOARD_WIDTH , BOARD_HEIGHT , selectMap);
        auto start = CLOCK_NOW();
//        renderGamePlay(renderer , game , gallery , textTexture , 0);
        bool isPause = false;
        Uint32 startTime = SDL_GetTicks();
        loadMusic("sound_and_music/sound_track.wav");
        while(game.isGameRunning())
        {
            while(SDL_PollEvent(&e))
            {
                buttonPause->handleEvent(&e);
                if(buttonPause->checkMoveDown())   isPause = !isPause;
                else interpretEvent(e , game);
            }
            if(!isPause)
            {
                auto end = CLOCK_NOW();
                ElapsedTime elapsed = end - start;
                Uint32 currentTime = SDL_GetTicks();
                Uint32 elapsedTimeReal = currentTime - startTime;
                if(elapsed.count() > STEP_DELAY)
                {
                    game.nextStep();
                    renderGamePlay(renderer , game , gallery , textTexture , elapsedTimeReal);
                    start = end;
                }
                SDL_Delay(200);
            }
            bool isGamePause = game.isGamePause();
            if(isGamePause)
            {
                quit = false;
                while(!quit)
                {
                    while(SDL_PollEvent(&e))
                    {
                        interpretEvent(e , game);
                        if(e.type == SDL_KEYUP) quit = true;
                    }
                }
                game.continuePlay();
            }
        }
        bool isGameOver = game.isGameOver();
        if(isGameOver)  loadWAV("sound_and_music/game_over.wav");
        else loadWAV("sound_and_music/game_win.wav");
        bool checkContinuePlay = isContinuePlay(buttonYes , buttonNo , renderer , gallery , textTexture , isGameOver);
        if(checkContinuePlay)
        {
//            game.playGameAgain();
            start = CLOCK_NOW();
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
