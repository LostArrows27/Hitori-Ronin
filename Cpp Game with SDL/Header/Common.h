#ifndef SDL_COMMON_H
#define SDL_COMMON_H

#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;
const char* WINDOW_TITLE = "Remember and Click Game";
enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

static SDL_Window* window;
static SDL_Renderer* render;

namespace Common_Func
{
    void init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            std::cout << "Error: SDL can't be initialized!" << std::endl << SDL_GetError() << std::endl;
        }
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!";
        }
        int iF = IMG_INIT_PNG;
        if (!(IMG_Init(iF) & iF)) {
            std::cout << "SDL_image could not initialize!" << std::endl << IMG_GetError() << std::endl;
        }
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        TTF_Init();
    }

    void back_render()
    {
        SDL_SetRenderDrawColor(render, 255, 255 ,255 ,255);
        SDL_RenderClear(render);
    }

    void present()
    {
        SDL_RenderPresent(render);
    }

    void quit()
    {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        window = NULL;
        render = NULL;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}


#endif // SDL_COMMON_H
