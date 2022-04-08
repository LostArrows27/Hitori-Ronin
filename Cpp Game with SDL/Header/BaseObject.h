#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int&x, const int& y){rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object;}
    virtual bool loadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};

BaseObject::BaseObject()
{
    p_object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::loadImg(std::string path, SDL_Renderer* render)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(render, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object = new_texture;

    return p_object != NULL;

}

void BaseObject::Render(SDL_Renderer* render, const SDL_Rect* clip)
{
    if(clip == NULL) rect_.w = SCREEN_WIDTH, rect_.h = SCREEN_HEIGHT;
    // neu NULL thi se keo bang man hinh
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(render, p_object, clip, &renderquad);
}

void BaseObject::Free()
{
    if(p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

#endif
