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

//void playMusicIntroBackground()
//{
//    Mix_Music* music = nullptr;
//    music = Mix_LoadMUS("sound_and_music/intro_sound_track.wav");
//    if(music == nullptr)
//        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
//    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( music , -1 );
//    else
//    {
//        if( Mix_PausedMusic() == 1 )  Mix_ResumeMusic();
//        else  Mix_PauseMusic();
//    }
//}

//void playSoundButton()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/click_button.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
//
//void playMusic()
//{
//    Mix_Music* music = nullptr;
//    music = Mix_LoadMUS("sound_and_music/sound_track.wav");
//    if(music == nullptr)
//        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
//    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( music , -1 );
//}
//
//void playEatBird()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/eat_bird.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
//
//void playEatBonus()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/eat_bonus.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
//
//void playError()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/error.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
//
//void playMove()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/snake_move.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
//
//void playGameOver()
//{
//    Mix_Chunk* scratch = nullptr;
//    scratch = Mix_LoadWAV("sound_and_music/snake_move.wav");
//    if(scratch == nullptr)
//        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
//    Mix_PlayChannel(-1 , scratch , 0);
//}
