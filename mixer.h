#ifndef MIXER__H
#define MIXER__H

#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>

using namespace std;

void loadMusic(string path);
void loadWAV(string path);

#endif // MIXER__H
