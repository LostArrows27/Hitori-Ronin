#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 595;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;

void init();
// create window and texture color

SDL_Texture* loadTexture(string path);
// load texture

void close();

int main(int argc, char* args[])
{
    init();
    texture = loadTexture("Image/Shinkai.png");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, NULL, NULL);
        SDL_RenderPresent(render);
    }
    close();
    return 0;
}

void init()
{
    window = SDL_CreateWindow("Shinkai Makoto picture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

SDL_Texture* loadTexture(string path)
{
    SDL_Texture* temp = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    temp = SDL_CreateTextureFromSurface(render, loadSurface);
    SDL_FreeSurface(loadSurface);
    return temp;
}

void close()
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
