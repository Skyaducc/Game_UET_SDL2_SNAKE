#ifndef GALLERY__H
#define GALLERY__H

#include <SDL.h>

enum PictureID
{
    PIC_BIRD = 0, PIC_BIG_BIRD,
    PIC_BACKGROUND,
    PIC_INTRO_BACKGROUND , PIC_BUTTON_PLAY , PIC_BUTTON_EXIT,
    PIC_HEART , PIC_HEART_NULL,
    PIC_WALL,
    PIC_MAP_ICE , PIC_MAP_SWAMP , PIC_MAP_VOLCANO , PIC_MAP_FOREST,
    PIC_MAP_FIELD , PIC_SNAKE_VERTICAL_FIELD , PIC_SNAKE_HORIZONTAL_FIELD , PIC_SNAKE_HEAD_FIELD ,
    PIC_SNAKE_BOT_VERTICAL_FIELD , PIC_SNAKE_BOT_HORIZONTAL_FIELD , PIC_SNAKE_BOT_HEAD_FIELD,
    PIC_ICON_NULL_B , PIC_ICON_NULL_O , PIC_ICON_NULL_N , PIC_ICON_NULL_U , PIC_ICON_NULL_S,
    PIC_ICON_B , PIC_ICON_O , PIC_ICON_N , PIC_ICON_U , PIC_ICON_S,
    PIC_B , PIC_O , PIC_N , PIC_U , PIC_S,
    PIC_WOOD_FRAME,
    PIC_COUNT
};

class Gallery
{
    SDL_Texture* pictures[PIC_COUNT];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string path , bool hasColorKey);
public:
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif // GALLERY__H
