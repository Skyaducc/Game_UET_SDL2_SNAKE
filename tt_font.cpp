#include "tt_font.h"

using namespace std;

Text::Text(SDL_Renderer* renderer_) : renderer(renderer_)
{
    Texture = NULL;
    Width = 0;
    Height = 0;
}

Text::~Text()
{
    free();
}

void Text::free()
{
    if(Texture != NULL)
    {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
        Width = 0;
        Height = 0;
    }
}

bool Text::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(Texture == NULL )
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
    return Texture != NULL;
}

void Text::setColor(Uint8 red , Uint8 green , Uint8 blue)
{
    SDL_SetTextureColorMod(Texture , red , green , blue);
}

void Text::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(Texture , blending);
}

void Text::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(Texture , alpha);
}

void Text::render(int x , int y , SDL_Rect* clip, double angle , SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x , y , Width , Height};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer , Texture , clip , &renderQuad , angle , center , flip);
}

int Text::getWidth()
{
    return Width;
}

int Text::getHeight()
{
    return Height;
}

void Text::loadGameFont(string s , int size)
{
    Font = TTF_OpenFont("dxlfont.ttf" , size);
    if(Font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
    {
        SDL_Color textColor = {0 , 0 , 255};
        if(!loadFromRenderedText(s , textColor))
        {
            printf( "Failed to render text texture!\n" );
        }
    }
}
