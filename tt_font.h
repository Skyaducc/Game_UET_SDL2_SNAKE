#ifndef TT_FONT__H
#define TT_FONT__H

#include <iostream>
#include <SDL_ttf.h>

using namespace std;
class Text
{
     TTF_Font* Font;
     SDL_Renderer* renderer;
     SDL_Texture* Texture;
public:
    Text(SDL_Renderer* renderer_);
    ~Text();
    bool loadFromRenderedText(string textureText , SDL_Color textColor);
    void free();
    void render(int x , int y , SDL_Rect* clip = nullptr , double angle = 0.0 , SDL_Point* center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    void loadGameFont(string s , int size);
private:
    int Width;
    int Height;
};

#endif // TT_FONT__H
