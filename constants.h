#ifndef CONSTANTS__H
#define CONSTANTS__H
#include <SDL.h>
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Snake_better_version Game";
const int CELL_SIZE =  30;

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;

const SDL_Color BOARD_COLOR = {0 , 0 , 0};
const SDL_Color LINE_COLOR = {128, 128, 128};

const int STEP_DELAY = 0.5;

const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};

#endif // CONSTANTS__H
