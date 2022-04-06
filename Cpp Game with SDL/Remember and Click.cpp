#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>
#include "Header/Game_Size.h"
#include "Header/Texture.h"

using namespace std;

int main(int argc, char* args[])
{
    Texture time_text;
    time_text.init();
    bool quit = false;
    SDL_Event e;
    Uint32 startTime = 0;
    std::stringstream timeText;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) startTime = SDL_GetTicks();
        }
        int k = (SDL_GetTicks() - startTime)/1000;
        timeText.str( "" );
        timeText << "TIME: " << k;
        time_text.loadMedia("Font/Need for font.ttf", timeText.str().c_str(), 40, 255, 0 , 0);
        time_text.onscreen(280, 200);
        time_text.present();
    }
    time_text.closing();
    return 0;
}

