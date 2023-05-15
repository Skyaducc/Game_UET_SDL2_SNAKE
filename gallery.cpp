#include "SDL_ultis.h"
#include "gallery.h"
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_): renderer(renderer_)
{
    for (int i=0 ; i<PIC_COUNT ; i++)   pictures[i] = nullptr;
    loadGamePictures();
}
Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
    {
        if(texture != nullptr)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}

SDL_Texture* Gallery::loadTexture(std::string path , bool hasColorKey)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else
    {
        Uint32 colorkey = SDL_MapRGB(loadedSurface->format , 255 , 255 , 255);
        if(hasColorKey) SDL_SetColorKey( loadedSurface, SDL_TRUE , colorkey );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[PIC_INTRO_BACKGROUND] = loadTexture("picture/introPic/intro_background.png" , 0);
    pictures[PIC_LEVEL_FRAME] = loadTexture("picture/introPic/level_frame.png" , 1);
    pictures[PIC_INTRO_FIELD] = loadTexture("picture/introPic/FIELD.png" , 1);
    pictures[PIC_INTRO_ICE] = loadTexture("picture/introPic/ICE.png" , 1);
    pictures[PIC_INTRO_FOREST] = loadTexture("picture/introPic/FOREST.png" , 1);
    pictures[PIC_INTRO_VOLCANO] = loadTexture("picture/introPic/VOLCANO.png" , 1);

    pictures[PIC_BIRD] = loadTexture("picture/birdPic/bird.png" , 0);
    pictures[PIC_BIG_BIRD] = loadTexture("picture/birdPic/bigBird.png" , 0);
    pictures[PIC_HEART] = loadTexture("picture/heartPic/heart.png" , 1);
    pictures[PIC_HEART_NULL] = loadTexture("picture/heartPic/heart_null.png" , 1);
    pictures[PIC_WOOD_FRAME] = loadTexture("picture/wood_frame.png" , 1);
    pictures[PIC_EASY] = loadTexture("picture/level/easy.png" , 1);
    pictures[PIC_MEDIUM] = loadTexture("picture/level/medium.png" , 1);
    pictures[PIC_HARD] = loadTexture("picture/level/hard.png" , 1);
    pictures[PIC_PAUSE_ICON] = loadTexture("picture/pause_icon.png" , 1);
    pictures[PIC_PAUSE_FRAME] = loadTexture("picture/pause_frame.png" , 1);

    pictures[PIC_BUTTON_EXIT] = loadTexture("picture/buttonPic/button_exit.png" , 0);
    pictures[PIC_BUTTON_PLAY] = loadTexture("picture/buttonPic/button_play.png" , 0);

    pictures[PIC_ICON_B] = loadTexture("picture/bonus/icon_B.png" , 1);
    pictures[PIC_ICON_O] = loadTexture("picture/bonus/icon_O.png" , 1);
    pictures[PIC_ICON_N] = loadTexture("picture/bonus/icon_N.png" , 1);
    pictures[PIC_ICON_U] = loadTexture("picture/bonus/icon_U.png" , 1);
    pictures[PIC_ICON_S] = loadTexture("picture/bonus/icon_S.png" , 1);
    pictures[PIC_ICON_NULL_B] = loadTexture("picture/bonus/icon_null_B.png" , 1);
    pictures[PIC_ICON_NULL_O] = loadTexture("picture/bonus/icon_null_O.png" , 1);
    pictures[PIC_ICON_NULL_N] = loadTexture("picture/bonus/icon_null_N.png" , 1);
    pictures[PIC_ICON_NULL_U] = loadTexture("picture/bonus/icon_null_U.png" , 1);
    pictures[PIC_ICON_NULL_S] = loadTexture("picture/bonus/icon_null_S.png" , 1);
    pictures[PIC_B] = loadTexture("picture/bonus/B.png" , 1);
    pictures[PIC_O] = loadTexture("picture/bonus/O.png" , 1);
    pictures[PIC_N] = loadTexture("picture/bonus/N.png" , 1);
    pictures[PIC_U] = loadTexture("picture/bonus/U.png" , 1);
    pictures[PIC_S] = loadTexture("picture/bonus/S.png" , 1);


    pictures[PIC_WALL] = loadTexture("picture/wall.png" , 0);
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("picture/snakePic/vertical_snake.png" , 1);
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("picture/snakePic/horizontal_snake.png" , 1);
    pictures[PIC_SNAKE_HEAD] = loadTexture("picture/snakePic/head_snake.png" , 1);
    pictures[PIC_SNAKE_TURN] = loadTexture("picture/snakePic/turn_snake.png" , 1);
    pictures[PIC_SNAKE_TAIL] = loadTexture("picture/snakePic/tail_snake.png" , 1);
    pictures[PIC_SNAKE_BOT_VERTICAL] = loadTexture("picture/snakePic/vertical_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_HORIZONTAL] = loadTexture("picture/snakePic/horizontal_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_HEAD] = loadTexture("picture/snakePic/head_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_TURN] = loadTexture("picture/snakePic/turn_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_TAIL] = loadTexture("picture/snakePic/tail_snake_bot.png" , 1);

    pictures[PIC_MAP_FIELD] = loadTexture("picture/mapPic/map_field.png" , 0);
    pictures[PIC_MAP_ICE] = loadTexture("picture/mapPic/map_ice.png" , 0);
    pictures[PIC_MAP_VOLCANO] = loadTexture("picture/mapPic/map_volcano.png" , 0);
    pictures[PIC_MAP_FOREST] = loadTexture("picture/mapPic/map_forest.png" , 0);
    pictures[PIC_MAPS] = loadTexture("picture/mapPic/maps.png" , 0);
    pictures[PIC_MAP_REVIEW_FIELD] = loadTexture("picture/reviewPic/field.png" , 0);
    pictures[PIC_MAP_REVIEW_ICE] = loadTexture("picture/reviewPic/ice.png" , 0);
    pictures[PIC_MAP_REVIEW_VOLCANO] = loadTexture("picture/reviewPic/volcano.png" , 0);
    pictures[PIC_MAP_REVIEW_FOREST] = loadTexture("picture/reviewPic/forest.png" , 0);

}
