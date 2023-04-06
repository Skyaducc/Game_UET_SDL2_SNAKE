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
    void setColor(Uint8 red , Uint8 green , Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x , int y , SDL_Rect* clip = NULL , double angle = 0.0 , SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
    void loadGameFont(string s , int size);
private:
    int Width;
    int Height;
};

#endif // TT_FONT__H

