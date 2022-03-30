#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
Texture colorAdjust;

void init();

void loadMedia();

void presenting();

void closing();

int main(int argc, char* args[])
{
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                        case SDLK_q:
                        r += 32;
                        break;
                        case SDLK_w:
                        g += 32;
                        break;
                        case SDLK_e:
                        b += 32;
                        break;
                        case SDLK_a:
                        r -= 32;
                        break;
                        case SDLK_s:
                        g -= 32;
                        break;
                        case SDLK_d:
                        b -= 32;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(render);
        colorAdjust.setColor(255, 128, 255);
        colorAdjust.renderer(0, 0, render, NULL);
        SDL_RenderPresent(render);
    }
    colorAdjust.free();
    closing();
    return 0;
}
void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}



void closing()
{
    colorAdjust.free();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}

void presenting()
{
    SDL_RenderPresent(render);
    SDL_Delay(40);
}

void loadMedia()
{
    colorAdjust.loadImage("Image/colors.png", render);
}
