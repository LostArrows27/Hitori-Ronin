#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
Texture background;
Texture Blending_image;
SDL_Rect temp[2];
// vung anh can cat


void init();

void loadMedia();

void presenting();

void closing();

int main(int argc, char* args[])
{
    for(int i = 0; i < 2; i++)
    {
        temp[i].x = 200;
        temp[i].y = 200;
        temp[i].w = SCREEN_WIDTH*2;
        temp[i].h = SCREEN_HEIGHT*2;
    }
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    Uint8 a = 255;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            else if( e.type == SDL_KEYDOWN )
					{
						if( e.key.keysym.sym == SDLK_UP )
						{
							if( a + 32 > 255 )
							{
								a = 255;
							}
							else
							{
								a += 32;
							}
						}
						else if( e.key.keysym.sym == SDLK_DOWN )
						{
							if( a - 32 < 0 )
							{
								a = 0;
							}
							else
							{
								a -= 32;
							}
						}
					}
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(render);
        background.renderer(0, 0, render, NULL);
        Blending_image.setAlpha(a);
        Blending_image.renderer(0, 0, render, NULL);
        SDL_RenderPresent(render);
    }
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
    background.free();
    Blending_image.free();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}

void loadMedia()
{
    Blending_image.loadImage("Image/001.jpg", render);
    background.loadImage("Image/002.jpg", render);
}
