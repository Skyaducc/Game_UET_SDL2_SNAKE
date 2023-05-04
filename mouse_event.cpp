#include <iostream>
#include "mouse_event.h"
#include "constants.h"

using namespace std;

Button::Button(int _x , int _y , int _w , int _h)
{
    x = _x , y = _y;
    w = _w , h = _h;
    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::handleEvent(SDL_Event* e)
{
//    cout << "handleEvent";
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int mX , mY;
        SDL_GetMouseState(&mX , &mY);
        cout << mX << " " << mY << endl;
        bool inside = true;
        if(mX < x) inside = false;
        else if(mX > x + w) inside = false;
        else if(mY < y )   inside = false;
        else if(mY > y + h) inside = false;
//        cout << mX << " " << mY << " " << x << " " << y << " " << x + w << " " << y + h << endl;
        if(!inside)
        {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

                case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

                case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

bool Button::checkMoveDown()
{
    return (currentSprite == BUTTON_SPRITE_MOUSE_DOWN);
}

//void Button::render(SDL_)
//{
//    buttonSpriteSheetTexture.render(mousePosition.x , mousePosition.y , &gSpriteClip[currentSprite]);
//}
