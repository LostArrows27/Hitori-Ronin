#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>
#include "Header/Close.h"
#include "Header/Game_Size.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;

void init();

SDL_Texture* loadSurface(string path);

int main(int argc, char* args[])
{
    init();
    texture = loadSurface("Image/hanabi.jpg");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
                //Clear screen
				SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( render );
				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor( render, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( render, &fillRect );
				//Render green outlined quad
				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
				SDL_SetRenderDrawColor( render, 0x00, 0xFF, 0x00, 0xFF );
				SDL_RenderDrawRect( render, &outlineRect );
				//Draw blue horizontal line
				SDL_SetRenderDrawColor( render, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderDrawLine( render, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0x00, 0xFF );
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( render, SCREEN_WIDTH / 2, i );
				}
				//Update screen
				SDL_RenderPresent( render );
    }
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

SDL_Texture* loadSurface(string path)
{
    SDL_Texture* temp = NULL;
    SDL_Surface* surface_temp = IMG_Load(path.c_str());
    temp = SDL_CreateTextureFromSurface(render, surface_temp);
    SDL_FreeSurface(surface_temp);
    return temp;
}


