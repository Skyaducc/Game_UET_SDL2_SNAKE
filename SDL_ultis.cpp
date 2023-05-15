#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "mixer.h"
#include "SDL_ultis.h"
#include "constants.h"
#include "gallery.h"
#include "Position.h"
#include "Game.h"

using namespace std;

void logSDLError(std::ostream& os , const std::string &msg, bool fatal)
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

void drawIntroBackground(SDL_Renderer* renderer , Gallery* gallery , Text* textTexture , int selectMap , int selectLevel)
{
    // draw intro background
    SDL_RenderCopy(renderer , gallery->getImage(PIC_INTRO_BACKGROUND) , NULL , NULL);
    // draw play button
    SDL_Rect frame = getRect(300 , -50 , 500 , 375);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_BUTTON_PLAY), NULL , &frame);
    // draw exit button
    frame = getRect(760 , 305 , 135 , 135);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_BUTTON_EXIT), NULL , &frame);
    // draw map
    SDL_Texture* Texture = nullptr;
    if(selectMap == 0)  Texture = gallery->getImage(PIC_MAP_REVIEW_FOREST);
    else if(selectMap == 1)  Texture = gallery->getImage(PIC_MAP_REVIEW_FIELD);
    else if(selectMap == 2)  Texture = gallery->getImage(PIC_MAP_REVIEW_ICE);
    else if(selectMap == 3)  Texture = gallery->getImage(PIC_MAP_REVIEW_VOLCANO);
    frame = getRect(100 , 280 , 200 , 150);
    SDL_RenderCopy(renderer , Texture , NULL , &frame);
    // draw level
    Texture = nullptr;
    if(selectLevel == 1)    Texture = gallery->getImage(PIC_EASY);
    else if(selectLevel == 2)   Texture = gallery->getImage(PIC_MEDIUM);
    else if(selectLevel == 3)   Texture = gallery->getImage(PIC_HARD);
    frame = getRect(-50 , -100 , 300 , 300);
    SDL_RenderCopy(renderer , Texture , NULL , &frame);
    //draw font
    Texture = nullptr;
    if(selectMap == 0)  Texture = gallery->getImage(PIC_INTRO_FOREST);
    else if(selectMap == 1)  Texture = gallery->getImage(PIC_INTRO_FIELD);
    else if(selectMap == 2)  Texture = gallery->getImage(PIC_INTRO_ICE);
    else if(selectMap == 3)  Texture = gallery->getImage(PIC_INTRO_VOLCANO);
    frame = getRect(50 , 330 , 300 , 300);
    SDL_RenderCopy(renderer , Texture , NULL , &frame);

    SDL_RenderPresent(renderer);
//    waitUntilKeyPressed();
}

void drawPauseGame(SDL_Renderer* renderer , Gallery* gallery)
{
    SDL_Rect frame = getRect(200 , 0 , 500 , 500);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_PAUSE_FRAME) , NULL , &frame);
    SDL_RenderPresent(renderer);
}

void drawBackground(SDL_Renderer* renderer , Gallery* gallery , const Game& game , int top , int left)
{
    SDL_Texture* Texture = nullptr;
    if(game.checkMapField()) Texture = gallery->getImage(PIC_MAP_FIELD);
    if(game.checkMapForest())  Texture = gallery->getImage(PIC_MAP_FOREST);
    if(game.checkMapIce())  Texture = gallery->getImage(PIC_MAP_ICE);
    if(game.checkMapVolcano())  Texture = gallery->getImage(PIC_MAP_VOLCANO);
    SDL_RenderCopy(renderer , Texture , NULL , NULL);
    SDL_Rect frame = getRect(-5 , -5 , 60 , 60);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_PAUSE_ICON) , NULL , &frame);
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

void drawSnake(SDL_Renderer* renderer , int left , int top , vector<Position> pos , Gallery* gallery , int currentDirection , bool isSnakeBot)
{
    cout << "drawSnake" << endl;
    SDL_Rect cell;
    cell.x = left + pos[pos.size()-1].x * CELL_SIZE;
    cell.y = top + pos[pos.size()-1].y * CELL_SIZE;
    cell.w = CELL_SIZE;
    cell.h = CELL_SIZE;
    double angle = 0;
    if(currentDirection == 0)   angle = -90;
    else if(currentDirection == 1)   angle = 90;
    else if(currentDirection == 2)  angle = 180;
    SDL_RenderCopyEx(renderer , gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_HEAD : PIC_SNAKE_HEAD) , NULL , &cell , angle , NULL , SDL_FLIP_NONE);
    for(int i=pos.size() - 2 ; i>=0 ; i--)
    {
        SDL_Rect cell;
        cell.x = left + pos[i].x * CELL_SIZE;
        cell.y = top + pos[i].y * CELL_SIZE;
        cell.w = CELL_SIZE;
        cell.h = CELL_SIZE;
        SDL_Texture* texture = nullptr;
        if(i == 0)
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_TAIL : PIC_SNAKE_TAIL);
            if(pos[i].y == pos[i+1].y)
            {
                if(pos[i].x == pos[i+1].x - 1)  angle = 0;
                else angle = 180;
            }
            else
            {
                if(pos[i].y == pos[i+1].y - 1)  angle = 90;
                else angle = -90;
            }
            SDL_RenderCopyEx(renderer , texture , NULL , &cell , angle , NULL , SDL_FLIP_NONE);
            break;
        }
        if((pos[i].y == pos[i+1].y - 1 && pos[i].x == pos[i-1].x + 1) || (pos[i].y == pos[i-1].y - 1 && pos[i].x == pos[i+1].x + 1))
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_TURN : PIC_SNAKE_TURN);
            angle = 0;
            SDL_RenderCopyEx(renderer , texture , NULL , &cell , angle , NULL , SDL_FLIP_NONE);
        }
        else if((pos[i].y == pos[i+1].y - 1 && pos[i].x == pos[i-1].x - 1) || (pos[i].y == pos[i-1].y - 1 && pos[i].x == pos[i+1].x - 1))
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_TURN : PIC_SNAKE_TURN);
            angle = 0;
            SDL_RenderCopyEx(renderer , texture , NULL , &cell , angle , NULL , SDL_FLIP_HORIZONTAL);
        }
        else if((pos[i].y == pos[i+1].y + 1 && pos[i].x == pos[i-1].x + 1) || (pos[i].y == pos[i-1].y + 1 && pos[i].x == pos[i+1].x + 1))
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_TURN : PIC_SNAKE_TURN);
            angle = 180;
            SDL_RenderCopyEx(renderer , texture , NULL , &cell , angle , NULL , SDL_FLIP_HORIZONTAL);
        }
        else if((pos[i].y == pos[i+1].y + 1 && pos[i].x == pos[i-1].x - 1 || pos[i].y == pos[i-1].y + 1 && pos[i].x == pos[i+1].x - 1))
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_TURN : PIC_SNAKE_TURN);
            angle = 180;
            SDL_RenderCopyEx(renderer , texture , NULL , &cell , angle , NULL , SDL_FLIP_NONE);
        }
        else if(pos[i].y == pos[i+1].y)
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_HORIZONTAL : PIC_SNAKE_HORIZONTAL);
            drawCell(renderer , left , top , pos[i] , texture);
        }
        else
        {
            texture = gallery->getImage((isSnakeBot) ? PIC_SNAKE_BOT_VERTICAL : PIC_SNAKE_VERTICAL);
            drawCell(renderer , left , top , pos[i] , texture);
        }
    }
}

void drawWall(SDL_Renderer* renderer , SDL_Texture* Texture , const Game &game , int top , int left)
{
    vector<Position> wallPosition = game.getWallPosition();
    for (Position p : wallPosition)
    {
        drawCell(renderer , left , top , p , Texture);
    }
}

void drawHeart(SDL_Renderer* renderer , Gallery* gallery , int heart , int top , int left)
{
    cout << "drawHeart" << endl;
    if(heart >= 1)
    {
        SDL_Rect frame = getRect(280 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART) , NULL , &frame);
    }
    else
    {
        SDL_Rect frame = getRect(280 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART_NULL) , NULL , &frame);
    }
    if(heart >= 2)
    {
        SDL_Rect frame = getRect(310 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART) , NULL , &frame);
    }
    else
    {
        SDL_Rect frame = getRect(310 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART_NULL) , NULL , &frame);
    }
    if(heart >= 3)
    {
        cout << "check 3 " << endl;
        SDL_Rect frame = getRect(340 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART) , NULL , &frame);
    }
    else
    {
        SDL_Rect frame = getRect(340 , 455 , 25 , 25);
        SDL_RenderCopy(renderer , gallery->getImage(PIC_HEART_NULL) , NULL , &frame);
    }
}

void drawBonus(SDL_Renderer* renderer , Gallery* gallery , const Game& game , int top , int left)
{
    map<char , bool> bonus = game.getBonus();
    PictureID picBonus[] = {PIC_ICON_B , PIC_ICON_O , PIC_ICON_N , PIC_ICON_U , PIC_ICON_S};
    PictureID picBonusNull[] = {PIC_ICON_NULL_B , PIC_ICON_NULL_O , PIC_ICON_NULL_N , PIC_ICON_NULL_U , PIC_ICON_NULL_S};
    PictureID pic[] = {PIC_B , PIC_O , PIC_N , PIC_U , PIC_S};
    SDL_Rect rect[] = {getRect(470 , 443 , 50 , 50),
                       getRect(500 , 443 , 50 , 50),
                       getRect(530 , 443 , 50 , 50),
                       getRect(560 , 443 , 50 , 50),
                       getRect(590 , 443 , 50 , 50)};
    for (int i=0 ; i<5 ; i++)
    {
        char c = BONUS[i];
        if(bonus[c])    SDL_RenderCopy(renderer , gallery->getImage(picBonus[i]) , NULL , &rect[i]);
        else SDL_RenderCopy(renderer , gallery->getImage(picBonusNull[i]) , NULL , &rect[i]);
    }
    pair<Position , pair<int , bool>> bonusPosition = game.getBonusPosition();
    if(bonusPosition.second.second)
    {
        drawCell(renderer , left , top , bonusPosition.first , gallery->getImage(pic[bonusPosition.second.first]));
    }
}

void renderGamePlay(SDL_Renderer* renderer , const Game& game , Gallery* gallery , Text* textTexture , Uint32 elapsedTimeReal)
{
    cout << "renderGamePlay" << endl;
    int top = 20 , left = 165;
    SDL_SetRenderDrawColor(renderer , BOARD_COLOR.r , BOARD_COLOR.g , BOARD_COLOR.b , 0);
    SDL_RenderClear(renderer);

    drawBackground(renderer , gallery , game , top , left);
    drawWall(renderer , gallery->getImage(PIC_WALL) , game , top , left);
    const int heart = game.getHeart();
    drawHeart(renderer , gallery , heart , top , left);
    drawBonus(renderer , gallery , game , top , left);

    vector<Position> vectorBirdPosition = game.getbirdPosition();
    if(vectorBirdPosition.size() == 1) drawBird(renderer , left , top , vectorBirdPosition[0]  , gallery);
    else drawBigBird(renderer , left , top , vectorBirdPosition[0]  , gallery);

    int currentDirection = (int)game.getDirection();
    drawSnake(renderer , left , top , game.getSnakePositions() , gallery , currentDirection , 0);
    int currentDirectionSnakeBot = (int)game.getDirectionBot();
    drawSnake(renderer , left , top , game.getSnakeBotPositions() , gallery , currentDirectionSnakeBot , 1);

    SDL_RenderPresent(renderer);
}

bool isContinuePlay(Button* buttonYes , Button* buttonNo , SDL_Renderer* renderer , Gallery* gallery , Text* textTexture , bool isGameOver)
{
    cout << "isContinuePlay" << endl;
    bool quit = false;
    SDL_Event e;
    SDL_Rect frame = getRect(270 , 50, 420 , 294);
    SDL_RenderCopy(renderer , gallery->getImage(PIC_WOOD_FRAME) , NULL , &frame);
    if(isGameOver)
    {
        textTexture->loadGameFont("GAME OVER" , 40);
        textTexture->render(310 , 130);
    }
    else
    {
        textTexture->loadGameFont("YOU WIN" , 40);
        textTexture->render(340 , 130);
    }
    textTexture->loadGameFont("Play Continue?" , 20);
    textTexture->render(350 , 200);
    textTexture->loadGameFont("YES" , 20);
    textTexture->render(350 , 250);
    textTexture->loadGameFont("NO" , 20);
    textTexture->render(585 , 250);
    SDL_RenderPresent(renderer);
    while( !quit )
    {
        while( SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                buttonYes->handleEvent(&e);
                if(buttonYes->checkMoveDown())
                {
                    return true;
                }
                buttonNo->handleEvent(&e);
                if(buttonNo->checkMoveDown())
                {
                    return false;
                }
            }
        }
    }
    return false;
}

void interpretEvent(SDL_Event e, Game& game)
{
    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        	case SDLK_w:
            {
                game.processUserInput(UP);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_s:
            {
                game.processUserInput(DOWN);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_a:
            {
                game.processUserInput(LEFT);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_d:
            {
                game.processUserInput(RIGHT);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
            case SDLK_UP:
            {
                game.processUserInput(UP);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_DOWN:
            {
                game.processUserInput(DOWN);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_LEFT:
            {
                game.processUserInput(LEFT);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        	case SDLK_RIGHT:
            {
                game.processUserInput(RIGHT);
                loadWAV("sound_and_music/snake_move.wav");
                break;
            }
        }
    }
}
