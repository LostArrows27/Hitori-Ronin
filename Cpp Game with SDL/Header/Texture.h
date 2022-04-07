#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include"Common.h"

using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    void loadImage(string path);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void renderer(int x, int y, SDL_Rect* clip);
    void renderer_flips(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setBlendMode(SDL_BlendMode blending);
    void loadFromRenderedText( std::string textureText, SDL_Color textColor);
    void setAlpha(Uint8 alpha);
    void loadMedia(string path, string text_content, int font_size, int r, int g, int b);
    void closing();
    void onscreen(int x, int y);
    int getWidth();
    int getHeight();
protected:
    SDL_Texture* texture;
    TTF_Font* gFont;
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

void Texture::loadMedia(string path, string text_content, int font_size, int r, int g, int b)
{
    gFont = TTF_OpenFont( path.c_str(), font_size );
    SDL_Color textColor = { r, g , b };
    loadFromRenderedText( text_content, textColor );
}

void Texture::closing()
{
    free();
    TTF_CloseFont(gFont);
    gFont = NULL;
}

void Texture::onscreen(int x, int y)
{
        renderer_flips( x, y);
}

void Texture::renderer_flips(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x, y, width, height };
    if (clip != NULL) {
          renderQuad.w = clip->w;
          renderQuad.h = clip->h;
    }
    // else se keo full kich thuoc anh that
    // co them tu them else de kich thuoc anh thanh that
	SDL_RenderCopyEx(render, texture, clip, &renderQuad, angle, center, flip);
}

void Texture::renderer(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, width, height };
    // if clip = NULL --> keo ra full man hinh --> thuong danh cho anh nen
    // else clip != NULL --> theo kich thuoc that cua anh --> thuong danh cho minimap va nhan vat
    if (clip != NULL) {
          renderQuad.w = clip->w;
          renderQuad.h = clip->h;
    }else{
        renderQuad.w = SCREEN_WIDTH;
        renderQuad.h = SCREEN_HEIGHT;
    }
	SDL_RenderCopy(render, texture, clip, &renderQuad);
}

void Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    texture = SDL_CreateTextureFromSurface( render, textSurface );
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface( textSurface );;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(texture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

int Texture::getHeight()
{
    return height;
}

int Texture::getWidth()
{
    return width;
}

#endif // SDL_TEXTURE_H



