#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include "Header/Game_Size.h"

using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    void loadImage(string path);
    void free();
    void renderer(int x, int y);
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    int width;
    int height;
};

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
Texture image;
Texture background;

void init();

void closing();

Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

void Texture::loadImage(string path)
{
    free();
    SDL_Texture* temp_texture = NULL;
    SDL_Surface* temp_surface = IMG_Load(path.c_str());
    SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
    temp_texture = SDL_CreateTextureFromSurface(render, temp_surface);
    width = temp_surface->w;
    height = temp_surface->h;
    SDL_FreeSurface(temp_surface);
    texture = temp_texture;
}

void Texture::free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::renderer(int x, int y)
{
    SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy( render, texture, NULL, &renderQuad );
}

int Texture::getHeight()
{
    return height;
}

int Texture::getWidth()
{
    return width;
}

void init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
}

void closing()
{
    image.free();
    background.free();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    window = NULL;
    render = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    init();
    image.loadImage("Image/foo.png");
    background.loadImage("Image/background.png");
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(render);
        background.renderer(0, 0);
        image.renderer(240, 190);
        SDL_RenderPresent(render);
    }
    closing();
    return 0;
}



