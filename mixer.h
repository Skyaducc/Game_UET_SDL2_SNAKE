#ifndef MIXER__H
#define MIXER__H

#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>

using namespace std;

void loadMusic(string path , Mix_Music* music);
void loadWAV(string path);
void playMusic(Mix_Music* music , Mix_Chunk* scratch , Mix_Chunk* high , Mix_Chunk* medium , Mix_Chunk* low);

#endif // MIXER__H
