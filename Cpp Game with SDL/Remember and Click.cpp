#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

int main(int argc, char* args[])
{
    Texture* text;
    text->init();
    text->loadMedia();
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;

        }
        text->onscreen();
    }
    text->closing();
    return 0;
}

