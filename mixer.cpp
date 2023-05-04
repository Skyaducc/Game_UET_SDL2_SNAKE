#include "mixer.h"

using namespace std;

void loadMusic(string path)
{

    Mix_Music* music = nullptr;
    music = Mix_LoadMUS(path.c_str());
    if(music == nullptr)
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( music , -1 );
}

void loadWAV(string path)
{
    Mix_Chunk* scratch = nullptr;
    scratch = Mix_LoadWAV(path.c_str());
    if(scratch == nullptr)
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    Mix_PlayChannel(-1 , scratch , 0);
}
