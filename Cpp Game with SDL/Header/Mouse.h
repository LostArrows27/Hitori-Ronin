#ifndef SDL_MOUSE_H
#define SDL_MOUSE_H

#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include "Texture.h"
#include "Game_Size.h"

using namespace std;

class Button
{
public:
    Button();
    // khoi tao Mouse trong (NULL)
    void setPosition(int x, int y);
    int get_currentSprite();
    // dieu chinh toa do theo bien x, y
    void handle_mouseEvent(SDL_Event* e);
    void render_button(Texture& temp, SDL_Renderer* temp_render, SDL_Rect temp_rect);
private:
    SDL_Point Pos;
    LButtonSprite currentSprite;
};

Button::Button()
{
    Pos.x = 0;
    Pos.y = 0;
    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

int Button::get_currentSprite()
{
    return currentSprite;
}

void Button::setPosition(int x, int y)
{
    Pos.x = x;
    Pos.y = y;
}

void Button::handle_mouseEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < Pos.x) inside = false;
        else if(x > Pos.x + BUTTON_WIDTH) inside = false;
        else if(y < Pos.y) inside = false;
        else if(y > Pos.y + BUTTON_HEIGHT) inside = false;

        if(!inside) currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        else
        {
            switch(e->type)
            {
            case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void Button::render_button(Texture& temp, SDL_Renderer* temp_render, SDL_Rect temp_rect)
{
        temp.renderer(Pos.x, Pos.y, temp_render, &temp_rect);
}

#endif // SDL_MOUSE_H
