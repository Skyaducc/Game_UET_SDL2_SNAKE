#include "SDL_ultis.h"
#include "gallery.h"
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_): renderer(renderer_)
{
    loadGamePictures();
}
Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Gallery::loadTexture(std::string path , bool hasColorKey)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else
    {
        Uint32 colorkey = SDL_MapRGB(loadedSurface->format , 255 , 255 , 255);
        if(hasColorKey) SDL_SetColorKey( loadedSurface, SDL_TRUE , colorkey );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[PIC_INTRO_BACKGROUND] = loadTexture("intro_background.png" , 0);
    pictures[PIC_BACKGROUND] = loadTexture("maps.png" , 0);
    pictures[PIC_BIRD] = loadTexture("bird.png" , 0);
    pictures[PIC_BIG_BIRD] = loadTexture("bigBird.png" , 0);
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("greenSnake/vertical.png" , 1);
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("greenSnake/horizontal.png" , 1);
    pictures[PIC_SNAKE_HEAD] = loadTexture("greenSnake/head.png" , 1);
    pictures[PIC_WALL] = loadTexture("wall.jpg" , 0);

    pictures[PIC_BUTTON_EXIT] = loadTexture("button_exit.png" , 0);
    pictures[PIC_BUTTON_PLAY] = loadTexture("button_play.png" , 0);


    pictures[PIC_MAP_ICE] = loadTexture("map_picture/map_ice.png" , 0);
    pictures[PIC_MAP_VOLCANO] = loadTexture("map_picture/map_volcano.png" , 0);
    pictures[PIC_MAP_FIELD] = loadTexture("map_picture/map_field.png" , 0);
    pictures[PIC_BACKGROUND_FIELD] = loadTexture("background_field.png" , 0);
    pictures[PIC_MAP_FOREST] = loadTexture("map_picture/map_forest.png" , 0);
    pictures[PIC_MAP_SWAMP] = loadTexture("map_picture/map_swamp.png" , 0);
}
