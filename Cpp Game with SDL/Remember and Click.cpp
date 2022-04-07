#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>
#include "Header/Texture.h"
#include "Header/Common.h"

using namespace std;


int main(int argc, char* args[])
{
    Texture time_text;
    Texture bg;
    Common_Func::init();
    bg.loadMedia("Font/Need for font.ttf", "YOUR GAME HAS BEGIN", 28, 255, 0, 0);
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
        int k = (SDL_GetTicks() - startTime)/100;
        int dv = k%10;
        int chuc = (k-dv)/10;
        timeText.str( "" );
        timeText << "TIME: " << chuc << "." << dv;
        time_text.loadMedia("Font/Need for font.ttf", timeText.str().c_str(), 40, 255, 0 , 255);
        Common_Func::back_render();
        time_text.onscreen(0, 0);
        bg.onscreen(100,200);
        Common_Func::present();
    }
    time_text.closing();
    bg.closing();
    Common_Func::quit();
    return 0;
}

