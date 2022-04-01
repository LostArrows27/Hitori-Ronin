#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"
#include "Header/Mouse.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ]; // phan texture muon lay

Texture gSpriteSheetTexture;

SDL_RendererFlip flipType = SDL_FLIP_NONE;

Button gButtons[ TOTAL_BUTTONS ];

int k = SCREEN_WIDTH/2;

void init();

void loadMedia();

void closing();

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
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            for(int i = 0; i < TOTAL_BUTTONS; ++i)
            {
                gButtons[i].handle_mouseEvent(&e);
            }
        }
        SDL_SetRenderDrawColor(render, 255, 255 ,255 ,255);
        SDL_RenderClear(render);
        for(int i = 0; i < TOTAL_BUTTONS; ++i)
        {
            int mouse_state = gButtons[i].get_currentSprite();
            gButtons[i].render_button(gSpriteSheetTexture, render, gSpriteClips[mouse_state]);
        }
        SDL_RenderPresent(render);
    }
    closing();
    return 0;
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

void loadMedia()
{
        gSpriteSheetTexture.loadImage("Image/button.png", render);
        for(int i = 0; i < BUTTON_SPRITE_TOTAL; ++i){
            gSpriteClips[ i ].x =  0;
            gSpriteClips[ i ].y =  i * 200;
            gSpriteClips[ i ].w = BUTTON_WIDTH;
            gSpriteClips[ i ].h = BUTTON_HEIGHT;
        }
        gButtons[ 0 ].setPosition(0, 0);
		gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
}

void closing()
{
    gSpriteSheetTexture.free();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}


