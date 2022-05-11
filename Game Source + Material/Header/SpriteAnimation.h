#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL.h"
#include "Transform.h"
#include "TextureMgr.h"

class SpritetAnimation {

    public:
        SpritetAnimation();
        void Update();
        void Draw(Transform* tf);
        void SetProps(int spriteRow, int frameCount, int speed);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        int m_CurrentFrame;
};

#endif // SPRITEANIMATION_H
