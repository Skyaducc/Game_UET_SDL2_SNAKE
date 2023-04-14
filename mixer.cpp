#include "mixer.h"

using namespace std;

void playMusic(Mix_Music* music , Mix_Chunk* scratch , Mix_Chunk* high , Mix_Chunk* medium , Mix_Chunk* low)
{
    music = Mix_LoadMUS("21_sound_effects_and_music/beat.wav");
    if( music == nullptr )
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    scratch = Mix_LoadWAV("21_sound_effects_and_music/scratch.wav");
    if( scratch == nullptr)
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    high = Mix_LoadWAV("21_sound_effects_and_music/high.wav");
    if( high == nullptr)
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    medium = Mix_LoadWAV("21_sound_effects_and_music/medium.wav");
    if( medium == nullptr)
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    low = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
    if( low == nullptr)
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                switch( e.key.keysym.sym )
                {
                    case SDLK_1:
                    {
                        Mix_PlayChannel(-1 , high , 0);
                        cout << 1 << endl;
                        break;
                    }
                    case SDLK_2:
                    {
                        Mix_PlayChannel( -1, medium, 0 );
                        cout << 2 << endl;
                        break;
                    }
                    case SDLK_3:
                    {
                        Mix_PlayChannel( -1, low, 0 );
                        cout << 3 << endl;
                        break;
                    }
                    case SDLK_4:
                    {
                        Mix_PlayChannel( -1, scratch, 0 );
                        cout << 4 << endl;
                        break;
                    }
                    case SDLK_9:
                    {
                        if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( music , -1 );
                        else
                        {
                            if( Mix_PausedMusic() == 1 )  Mix_ResumeMusic();
                            else  Mix_PauseMusic();
                        }
                        cout << 9 << endl;
                        break;
                    }
                    case SDLK_0:
                    {
                        Mix_HaltMusic();
                        cout << 0 << endl;
                        break;
                    }
                }
            }
        }
    }
}
