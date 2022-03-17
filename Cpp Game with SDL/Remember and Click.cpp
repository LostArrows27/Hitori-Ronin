#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 595;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* stretchedImage = NULL;

void init();
// tao cua so va surface

SDL_Surface* loadSurface(string path);
// dua anh len surface

void close();
// giai phong chuong trinh

int main(int argc, char* args[])
{
    init();
    stretchedImage = loadSurface("Rem.png");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_Rect temp;
        temp.x = 0;
        temp.y = 0;
        temp.w = SCREEN_WIDTH;
        temp.h = SCREEN_HEIGHT;
        SDL_BlitScaled(stretchedImage, NULL, surface, &temp);
        SDL_UpdateWindowSurface(window);
    }
    close();
    return 0;
}

void init()
{
    window = SDL_CreateWindow("Waifu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
}

SDL_Surface* loadSurface(string path)
{
    SDL_Surface* stretched = NULL;
    SDL_Surface* temp = IMG_Load(path.c_str());
    stretched = SDL_ConvertSurface(temp, surface->format, 0);
    SDL_FreeSurface(temp);
    return stretched;
}

void close()
{
    SDL_FreeSurface(stretchedImage);
    stretchedImage = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}
