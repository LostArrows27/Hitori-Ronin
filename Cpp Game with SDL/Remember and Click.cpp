#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>
#include"Header/Close.h"
#include"Header/Game_Size.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture_1 = NULL;
SDL_Texture* texture_2 = NULL;
SDL_Texture* texture_3 = NULL;
SDL_Texture* texture_4 = NULL;

void init();

SDL_Texture* loadSurface(string path);

int main(int argc, char* args[])
{
    init();
    texture_1 = loadSurface("Image/001.jpg");
    texture_2 = loadSurface("Image/002.jpg");
    texture_3 = loadSurface("Image/003.jpg");
    texture_4 = loadSurface("Image/004.jpg");
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
        SDL_Rect temp;
        temp.x = 0;
        temp.y = 0;
        temp.h = SCREEN_HEIGHT/2;
        temp.w = SCREEN_WIDTH/2;
        SDL_RenderSetViewport(render, &temp);
        SDL_RenderCopy(render, texture_1, NULL, NULL);
        ////
        SDL_Rect temp2;
        temp2.x = SCREEN_WIDTH/2;
        temp2.y = 0;
        temp2.h = SCREEN_HEIGHT/2;
        temp2.w = SCREEN_WIDTH/2;
        SDL_RenderSetViewport(render, &temp2);
        SDL_RenderCopy(render, texture_2, NULL, NULL);
        ////
        SDL_Rect temp3;
        temp3.x = 0;
        temp3.y = SCREEN_HEIGHT/2;
        temp3.h = SCREEN_HEIGHT/2;
        temp3.w = SCREEN_WIDTH/2;
        SDL_RenderSetViewport(render, &temp3);
        SDL_RenderCopy(render, texture_3, NULL, NULL);
        ///
        SDL_Rect temp4;
        temp4.x = SCREEN_WIDTH/2;
        temp4.y = SCREEN_HEIGHT/2;
        temp4.h = SCREEN_HEIGHT/2;
        temp4.w = SCREEN_WIDTH/2;
        SDL_RenderSetViewport(render, &temp4);
        SDL_RenderCopy(render, texture_4, NULL, NULL);
        SDL_RenderPresent(render);
    }
    close(window, render, texture_1);
    close(window, render, texture_2);
    close(window, render, texture_3);
    close(window, render, texture_4);
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render,0xFF, 0xFF, 0xFF, 0xFF);
}

SDL_Texture* loadSurface(string path)
{
    SDL_Texture* temp = NULL;
    SDL_Surface* temp_surface = IMG_Load(path.c_str());
    temp = SDL_CreateTextureFromSurface(render, temp_surface);
    SDL_FreeSurface(temp_surface);
    return temp;
}

