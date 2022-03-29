#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    void loadImage(string path, SDL_Renderer* render);
    void free();
    void renderer(int x, int y, SDL_Renderer* render, SDL_Rect* clip = NULL);
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    int width;
    int height;
};

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

void Texture::loadImage(string path, SDL_Renderer* render)
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

void Texture::renderer(int x, int y, SDL_Renderer* render, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, width, height };
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
	SDL_RenderCopy(render, texture, clip, &renderQuad);
}

int Texture::getHeight()
{
    return height;
}

int Texture::getWidth()
{
    return width;
}




