#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL.h"
#include "Animation.h"

class SpritetAnimation : public Animation {

    public:
        SpritetAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale=1, float yScale=1);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int speed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        SDL_RendererFlip m_Flip;
        std::string m_TextureID;
};

#endif // SPRITEANIMATION_H
