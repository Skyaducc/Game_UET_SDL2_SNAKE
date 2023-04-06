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

SDL_Texture* Gallery::loadTexture(std::string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else
    {
//        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 255 , 0) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[PIC_INTRO_BACKGROUND] = loadTexture("intro_background.jpg");
    pictures[PIC_BACKGROUND] = loadTexture("background1.jpg");
    pictures[PIC_BIRD] = loadTexture("bird.png");
    pictures[PIC_BIG_BIRD] = loadTexture("bigBird.png");
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("snake_vertical.png");
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("snake_horizontal.png");
    pictures[PIC_SNAKE_HEAD] = loadTexture("snake_head.png");
    pictures[PIC_GAME_MENU] = loadTexture("textframe_gamemenu.png");
    pictures[PIC_BACKGROUND_FRAME] = loadTexture("background_frame.png");
}
