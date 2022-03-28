#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Close.h";
#include "Header/Game_Size.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;

void init();

SDL_Texture* loadTexture(string path);

int main(int argc, char* args[])
{
    init();
    texture = loadTexture("Image/hanabi.jpg");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, NULL, NULL);
        SDL_RenderPresent(render);
    }
    close(window, render, texture);
    return 0;
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

SDL_Texture* loadTexture(string path)
{
    SDL_Texture* temp = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    temp = SDL_CreateTextureFromSurface(render, loadSurface);
    SDL_FreeSurface(loadSurface);
    return temp;
}

