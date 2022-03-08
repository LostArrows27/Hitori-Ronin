#include<SDL.h>
#include<iostream>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
    }
    else{
        window = SDL_CreateWindow("First Lesson", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            cout << "Window could not be created! SDL_Error:" << SDL_GetError();
        }else
        {
            for(int i = 15; 3*i < 1000; i++){
                screenSurface = SDL_GetWindowSurface(window);
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, i, 2*i, 3*i ) );
                SDL_UpdateWindowSurface( window );
                SDL_Delay (50);
            }
        }

    }
}
