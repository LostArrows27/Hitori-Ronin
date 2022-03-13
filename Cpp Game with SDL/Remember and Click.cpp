#include<iostream>
#include<SDL.h>

using namespace std;

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* image = NULL;

void close()
{
    SDL_FreeSurface(image);
    image = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    SDL_Event e;
    bool quit =false;
    window = SDL_CreateWindow("Creating Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT) quit = true;
        }
        image = SDL_LoadBMP("2nd_lesson_image/testing_02.bmp");
        SDL_BlitSurface(image,NULL, surface, NULL);
        SDL_UpdateWindowSurface(window);
    }
    close();
    return 0;
}
