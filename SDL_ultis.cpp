#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDL_ultis.h"
#include "constants.h"
#include "gallery.h"
#include "Position.h"
#include "Game.h"

using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        // Khởi tạo SDL_mixer không thành công
        printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
    }
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) return;
        SDL_Delay(100);
    }
}

SDL_Rect getRect(int x , int y , int w , int h)
{
    SDL_Rect res;
    res.x = x , res.y = y , res.w = w , res.h = h;
    return res;
}

void drawIntroBackground(SDL_Renderer* renderer , Gallery* gallery , Text* textTexture)
{
    // draw intro background
    SDL_RenderCopy(renderer , gallery->getImage(PIC_INTRO_BACKGROUND) , NULL , NULL);
    // draw play button
    SDL_Rect frame = getRect(300 , -50 , 500 , 375);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_BUTTON_PLAY), NULL , &frame);
    // draw exit button
    frame = getRect(760 , 305 , 135 , 135);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_BUTTON_EXIT), NULL , &frame);

//    frame = getRect(370 , 270 , 170 , 60);
//    SDL_RenderCopy(renderer , gallery->getImage(PIC_GAME_MENU) , NULL , &frame);
//    textTexture->loadGameFont("MAPS" , 30);
//    textTexture->render(400 , 290);
//
//    frame = getRect(370 , 360 , 170 , 60);
//    SDL_RenderCopy(renderer , gallery->getImage(PIC_GAME_MENU) , NULL , &frame);
//    textTexture->loadGameFont("QUIT" , 30);
//    textTexture->render(400 , 380);

    SDL_RenderPresent(renderer);
//    waitUntilKeyPressed();
}

void drawBackground(SDL_Renderer* renderer , Gallery* gallery , Text* textTexture , const Game& game , int top , int left)
{
    SDL_RenderCopy(renderer , gallery->getImage(PIC_MAP_FIELD) , NULL , NULL);
    textTexture->loadGameFont("YOUR SCORE: " , 13);
    textTexture->render(700 , 5);
    string score_string = to_string(game.getScore());
    textTexture->loadGameFont(score_string , 13);
    textTexture->render(850 , 5);

//    SDL_Rect frame = getRect(left , top , 575 , 410);
//    SDL_RenderCopy(renderer , gallery->getImage(PIC_BACKGROUND_FIELD) , NULL , &frame);
}

void drawCell(SDL_Renderer* renderer , int left , int top , Position pos , SDL_Texture* Texture)
{
    SDL_Rect cell;
    cell.x = left + pos.x * CELL_SIZE;
    cell.y = top + pos.y * CELL_SIZE;
    cell.w = CELL_SIZE;
    cell.h = CELL_SIZE;
    SDL_RenderCopy(renderer , Texture , NULL , &cell);
}

void drawBird(SDL_Renderer* renderer , int left , int top , Position pos , Gallery* gallery)
{
    drawCell(renderer , left , top , pos , gallery->getImage(PIC_BIRD));
}

void drawBigBird(SDL_Renderer* renderer , int left , int top , Position pos , Gallery* gallery)
{
    SDL_Rect cell;
    cell.x = left + pos.x * CELL_SIZE;
    cell.y = top + pos.y * CELL_SIZE;
    cell.w = CELL_SIZE * 2;
    cell.h = CELL_SIZE * 2;
    SDL_RenderCopy(renderer , gallery->getImage(PIC_BIG_BIRD) , NULL , &cell);
}

void drawSnake(SDL_Renderer* renderer , int left , int top , vector<Position> pos , Gallery* gallery)
{
    drawCell(renderer , left , top , pos[pos.size() - 1] , gallery->getImage(PIC_SNAKE_HEAD));
    for(int i=pos.size() - 2 ; i>=0 ; i--)
    {
        SDL_Texture* texture = gallery->getImage(pos[i].y == pos[i+1].y ? PIC_SNAKE_HORIZONTAL : PIC_SNAKE_VERTICAL);
        drawCell(renderer , left , top , pos[i] , texture);
    }
}

void drawVerticalLine(SDL_Renderer* renderer , int left , int top , int cells)
{
    SDL_SetRenderDrawColor(renderer , LINE_COLOR.r , LINE_COLOR.g , LINE_COLOR.b , 0);
    SDL_RenderDrawLine(renderer , left , top , left , top + cells * CELL_SIZE);
}

void drawHorizontalLine(SDL_Renderer* renderer , int left , int top , int cells)
{
    SDL_SetRenderDrawColor(renderer , LINE_COLOR.r , LINE_COLOR.g , LINE_COLOR.b , 0);
    SDL_RenderDrawLine(renderer , left , top , left + cells * CELL_SIZE , top);
}

void drawWall(SDL_Renderer* renderer , SDL_Texture* Texture , const Game &game , int top , int left)
{
    vector<Position> wallPosition = game.getWallPosition();
    for (Position p : wallPosition)
    {
        drawCell(renderer , left , top , p , Texture);
    }
}

void renderGamePlay(SDL_Renderer* renderer , const Game& game , Gallery* gallery , Text* textTexture)
{
//    cout << "check" << endl;
    int top = 20 , left = 165;
    SDL_SetRenderDrawColor(renderer , BOARD_COLOR.r , BOARD_COLOR.g , BOARD_COLOR.b , 0);
    SDL_RenderClear(renderer);

    for (int x=0 ; x<=BOARD_WIDTH ; x++)
        drawVerticalLine(renderer , left + x * CELL_SIZE , top , BOARD_HEIGHT);
    for (int y=0 ; y<=BOARD_HEIGHT ; y++)
        drawHorizontalLine(renderer , left , top + y * CELL_SIZE , BOARD_WIDTH);
    drawBackground(renderer , gallery , textTexture , game , top , left);
    drawWall(renderer , gallery->getImage(PIC_WALL) , game , top , left);

    vector<Position> vectorBirdPosition = game.getbirdPosition();
    if(vectorBirdPosition.size() == 1) drawBird(renderer , left , top , vectorBirdPosition[0]  , gallery);
    else drawBigBird(renderer , left , top , vectorBirdPosition[0]  , gallery);
    drawSnake(renderer , left , top , game.getSnakePositions() , gallery);
    drawSnake(renderer , left , top , game.getSnakeBotPositions() , gallery);

    SDL_RenderPresent(renderer);
}


void interpretEvent(SDL_Event e, Game& game)
{
    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        	case SDLK_UP: game.processUserInput(UP); break;
        	case SDLK_DOWN: game.processUserInput(DOWN); break;
        	case SDLK_LEFT: game.processUserInput(LEFT); break;
        	case SDLK_RIGHT: game.processUserInput(RIGHT); break;
        }
    }
}
