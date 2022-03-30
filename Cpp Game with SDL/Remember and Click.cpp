#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Rect gSpriteClips[ 5 ];
Texture gSpriteSheetTexture[4];
Texture background;
int k = SCREEN_WIDTH-20;

void init();

void loadMedia();

void closing();

void presenting();

void moving(int& k, int step);

void render_background();

int main(int argc, char* args[])
{
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            render_background();
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    moving(k, -7);
                    break;
                case SDLK_RIGHT:
                    moving(k, 7);
                    break;
                }
            }
        }
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

void loadMedia()
{
        background.loadImage("Image/background.png", render);
        for(int i = 0; i < 4; i++){
            gSpriteSheetTexture[i].loadImage("Image/sheet.png", render);
        }
        for(int i = 0; i < 4; i++){
            gSpriteClips[ i ].x =  0;
            gSpriteClips[ i ].y =  0;
            gSpriteClips[ i ].w = 64;
            gSpriteClips[ i ].h = 205;
        }
        for(int i = 1; i < 4; i++) gSpriteClips[i].x = 64*i;
}

void closing()
{
    for(int i = 0; i < 4; i++) gSpriteSheetTexture[i].free();
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
    SDL_Delay(30);
}

void moving(int& k, int step)
{
    for(int i = 0; i < 4; i++){
    background.renderer(0, 0, render, NULL);
    gSpriteSheetTexture[i].renderer( k, 190, render, &gSpriteClips[i] );
    presenting();
    SDL_RenderClear(render);
    k = k + step;
    }
    if(k > SCREEN_WIDTH) k = -28;
    if(k < -30) k = SCREEN_WIDTH-20;
}

void render_background()
{
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
    background.renderer(0, 0, render, NULL);
}
