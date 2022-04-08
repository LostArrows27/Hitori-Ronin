#ifndef SDL_COMMON_H
#define SDL_COMMON_H

#include <SDL.h>
#include <windows.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

static SDL_Window* window = NULL;
static SDL_Renderer* render = NULL;
static SDL_Event e;

const int SCREEN_WIDTH = 1920/2;
const int SCREEN_HEIGHT = 1080/2;
const int SCREEN_BPP = 32;

const char* WINDOW_TITLE = "The lost Ronin";

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

#define TILE_SIZE 64

#define MAX_MAX_X 400
#define MAX_MAX_Y 10

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

#endif // SDL_COMMON_H
