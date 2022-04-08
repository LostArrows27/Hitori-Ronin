#ifndef SDL_CHARACTER_H
#define SDL_CHARACTER_H

#include "Common.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 0.5

class Character : public BaseObject
{
public:
    Character();
    ~Character();
    enum Walktype
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1
    };
    bool LoadImg(std::string path, SDL_Renderer* render);
    void Show(SDL_Renderer* render);
    void HandleInput(SDL_Event e, SDL_Renderer* render);
    void Set_Clip();
    void DoPlayer();
private:
    float x_val_;
    float y_val_;
    // luong tang len
    float x_pos_;
    float y_pos_;
    // vi tri hien tai
    int width_frame_;
    int height_frame_;
    // chieu cao nhan vat
    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_; // di chuyen trai hay phai
    SDL_RendererFlip flip;

};

Character::Character()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.up_ = 0;
}

Character::~Character()
{
    Free();
}

bool Character::LoadImg(std::string path, SDL_Renderer* render)
{
    bool ret = BaseObject::loadImg(path, render);
    if(ret == true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Character::Set_Clip()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for(int i = 0; i < 8; i++)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void Character::Show(SDL_Renderer* render)
{
   if(status_ == WALK_LEFT)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if(status_ == WALK_RIGHT)
    {
        flip = SDL_FLIP_NONE;
    }
    if(input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_ ++;
    }else
    {
        frame_ = 0;
        // doan nay co the xu li de nhan vat nhun nhay khi khong di chuyen
    }

    if(frame_ >= 8) frame_ = 0;
    rect_.x = x_pos_ - 50;
    // tang giam vi ban dau render theo x_pos va y_pos se o vi tri 0, 0
    rect_.y = y_pos_+ 250;
    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopyEx(render, p_object, current_clip, &renderQuad, 0.0, NULL, flip);
}

void Character::HandleInput(SDL_Event e, SDL_Renderer* render)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            break;
        }
    }else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type_.right_ = 0;

            }
            break;
        case SDLK_LEFT:
            {
                input_type_.left_ = 0;
            }
            break;
        }
    }
}

void Character::DoPlayer()
{
    x_val_ = 0;
    y_val_ += 0.8;

    //if(y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;
    if(input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
        x_pos_ -= PLAYER_SPEED;
    }else if(input_type_.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
        x_pos_ += PLAYER_SPEED;
    }
    if(x_pos_ > SCREEN_WIDTH - 120) x_pos_ -= PLAYER_SPEED;
    else if(x_pos_ < -80) x_pos_ += PLAYER_SPEED;
}


#endif // SDL_CHARACTER_H

