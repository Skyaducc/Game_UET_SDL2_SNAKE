#include "tt_font.h"

using namespace std;

Text::Text(SDL_Renderer* renderer_) : renderer(renderer_)
{
    Font = nullptr;
    Texture = nullptr;
    Width = 0;
    Height = 0;
}

Text::~Text()
{
    free();
}

void Text::free()
{
    if(Texture != nullptr)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
        Width = 0;
        Height = 0;
    }
}

bool Text::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(Texture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            Width = textSurface->w;
            Height = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return Texture != nullptr;
}


void Text::render(int x , int y , SDL_Rect* clip, double angle , SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x , y , Width , Height};
    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer , Texture , clip , &renderQuad , angle , center , flip);
}

void Text::loadGameFont(string s , int size)
{
    Font = TTF_OpenFont("dxlfont.ttf" , size);
    if(Font == nullptr )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
    {
        SDL_Color textColor = {128 , 0 , 128};
        if(!loadFromRenderedText(s , textColor))
        {
            printf( "Failed to render text texture!\n" );
        }
    }
}
