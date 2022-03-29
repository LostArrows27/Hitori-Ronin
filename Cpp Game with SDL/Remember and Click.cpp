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

void init();

void loadMedia();

void closing();

void presenting();

int main(int argc, char* args[])
{
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    int k = 620;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        background.renderer(0, 0, render, NULL);
        for(int i = 0; i < 4; i++){
            background.renderer(0, 0, render, NULL);
            gSpriteSheetTexture[i].renderer( k, 190, render, &gSpriteClips[i] );
            presenting();
            SDL_RenderClear(render);
            k = k - 5;
        }
        if(k < -50) k = 620;
        k = k - 5;
        //if(k < 0) k = 420
        cout << k << endl;
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
        gSpriteSheetTexture[0].loadImage("Image/sheet.png", render);
        gSpriteSheetTexture[1].loadImage("Image/sheet.png", render);
        gSpriteSheetTexture[2].loadImage("Image/sheet.png", render);
        gSpriteSheetTexture[3].loadImage("Image/sheet.png", render);
        gSpriteClips[ 0 ].x =  0;
		gSpriteClips[ 0 ].y =  0;
		gSpriteClips[ 0 ].w = 64;
		gSpriteClips[ 0 ].h = 205;

		//Set top right sprite
		gSpriteClips[ 1 ].x = 64;
		gSpriteClips[ 1 ].y =  0;
		gSpriteClips[ 1 ].w = 64;
		gSpriteClips[ 1 ].h = 205;

		//Set bottom left sprite
		gSpriteClips[ 2 ].x =  128 ;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w = 64;
		gSpriteClips[ 2 ].h = 205;

		//Set bottom right sprite
		gSpriteClips[ 3 ].x = 192;
		gSpriteClips[ 3 ].y = 0;
		gSpriteClips[ 3 ].w = 64;
		gSpriteClips[ 3 ].h = 205;
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
    SDL_Delay(50);
}


