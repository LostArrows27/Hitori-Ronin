#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

Texture background;

Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;


void init();

void loadMedia(); // containing music and image

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
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN)
            {
               switch( e.key.keysym.sym )
						{
							case SDLK_1:
							Mix_PlayChannel( -1, gHigh, 0 );
							break;
							case SDLK_2:
							Mix_PlayChannel( -1, gMedium, 0 );
							break;
							case SDLK_3:
							Mix_PlayChannel( -1, gLow, 0 );
							break;
							case SDLK_4:
							Mix_PlayChannel( -1, gScratch, 0 );
							break;
							case SDLK_9:
							if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 );
							else
							{
								if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
								else Mix_PauseMusic();
							}
							break;
							case SDLK_0:
							Mix_HaltMusic();
							break;
						}
            }
            SDL_SetRenderDrawColor(render, 255, 255 ,255 ,255);
            SDL_RenderClear(render);
            background.renderer(0, 0, render, NULL);
            SDL_RenderPresent(render);
        }
    }
    closing();
    return 0;
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void loadMedia()
{
        background.loadImage("Image/musicbg.png", render);
        gMusic = Mix_LoadMUS( "Sound/beat1.wav" );
        gScratch = Mix_LoadWAV( "Sound/scratch1.wav" );
        gHigh = Mix_LoadWAV( "Sound/high1.wav" );
        gMedium = Mix_LoadWAV( "Sound/medium1.wav" );
        gLow = Mix_LoadWAV( "Sound/low1.wav" );
}

void closing()
{
    background.free();
    Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}

