#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
Texture image;
Texture background;
Texture image_sec;

void init();

void closing();

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

void closing()
{
    image.free();
    background.free();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    init();
    image.loadImage("Image/foo.png", render);
    background.loadImage("Image/background.png", render);
    image_sec.loadImage("Image/foo.png", render);
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(render);
        background.renderer(0, 0, render);
        image.renderer(240, 190, render);
        image_sec.renderer(280, 190, render);
        SDL_RenderPresent(render);
    }
    closing();
    return 0;
}


