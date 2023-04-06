#ifndef GALLERY__H
#define GALLERY__H

#include <SDL.h>

enum PictureID
{
    PIC_BIRD = 0, PIC_BIG_BIRD , PIC_SNAKE_VERTICAL,
    PIC_SNAKE_HORIZONTAL, PIC_SNAKE_HEAD, PIC_COUNT,
    PIC_BACKGROUND, PIC_INTRO_BACKGROUND , PIC_BACKGROUND_FRAME , PIC_GAME_MENU
};

class Gallery
{
    SDL_Texture* pictures[PIC_COUNT];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string path);
public:
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif // GALLERY__H
