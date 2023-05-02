#ifndef MOUSE_EVENT__H
#define MOUSE_EVENT__H
#include <SDL.h>
using namespace std;

enum buttonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_MOUSE_TOTALS = 4
};

class Button
{
private:
    buttonSprite currentSprite;
public:
    int x , y , w , h;
    Button(int _x , int _y , int _w , int _h);
    void setPosition(int x , int y);
    void handleEvent(SDL_Event* e);
    bool checkMoveDown();
    int getButtonSprite() { return (int)currentSprite; }
};
#endif // MOUSE_EVENT__H
