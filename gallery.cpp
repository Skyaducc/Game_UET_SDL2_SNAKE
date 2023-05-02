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
    pictures[PIC_INTRO_BACKGROUND] = loadTexture("intro_background.png" , 0);
    pictures[PIC_BIRD] = loadTexture("bird.png" , 0);
    pictures[PIC_BIG_BIRD] = loadTexture("bigBird.png" , 0);
    pictures[PIC_HEART] = loadTexture("heart.png" , 1);
    pictures[PIC_HEART_NULL] = loadTexture("heart_null.png" , 1);

    pictures[PIC_BUTTON_EXIT] = loadTexture("button_exit.png" , 0);
    pictures[PIC_BUTTON_PLAY] = loadTexture("button_play.png" , 0);

    pictures[PIC_MAP_FIELD] = loadTexture("field_world/map_field.png" , 0);
    pictures[PIC_WALL] = loadTexture("field_world/wall.png" , 0);
    pictures[PIC_SNAKE_VERTICAL_FIELD] = loadTexture("field_world/vertical_snake.png" , 1);
    pictures[PIC_SNAKE_HORIZONTAL_FIELD] = loadTexture("field_world/horizontal_snake.png" , 1);
    pictures[PIC_SNAKE_HEAD_FIELD] = loadTexture("field_world/head_snake.png" , 1);
    pictures[PIC_SNAKE_BOT_VERTICAL_FIELD] = loadTexture("field_world/vertical_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_HORIZONTAL_FIELD] = loadTexture("field_world/horizontal_snake_bot.png" , 1);
    pictures[PIC_SNAKE_BOT_HEAD_FIELD] = loadTexture("field_world/head_snake_bot.png" , 1);

    pictures[PIC_MAP_ICE] = loadTexture("map_picture/map_ice.png" , 0);
    pictures[PIC_MAP_VOLCANO] = loadTexture("map_picture/map_volcano.png" , 0);
    pictures[PIC_MAP_FOREST] = loadTexture("map_picture/map_forest.png" , 0);
    pictures[PIC_MAP_SWAMP] = loadTexture("map_picture/map_swamp.png" , 0);
    pictures[PIC_WOOD_FRAME] = loadTexture("wood_frame.png" , 1);

}
