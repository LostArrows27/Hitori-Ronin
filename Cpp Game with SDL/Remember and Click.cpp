#include<iostream>
#include<SDL.h>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Surface* stretchedImage = NULL;

void init()
{
    window = SDL_CreateWindow("Convert Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimized = NULL;
    SDL_Surface* temp = SDL_LoadBMP(path.c_str());
    optimized = SDL_ConvertSurface(temp, surface->format, 0);
    SDL_FreeSurface(temp);
    return optimized;
}

void close()
{
    SDL_FreeSurface(stretchedImage);
    stretchedImage = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    init();
    stretchedImage = loadSurface("5th_lesson_image/stretch.bmp");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(stretchedImage, NULL, surface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }
    close();
    return 0;
}
