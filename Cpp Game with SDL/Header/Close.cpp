//#include<iostream>
//#include<SDL.h>
#include "Close.h"
//#include<SDL_image.h>


//using namespace std;

void close(SDL_Window* window, SDL_Renderer* render, SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}
