#include "SpriteAnimation.h"

SpritetAnimation::SpritetAnimation(){}

void SpritetAnimation::Draw(Transform* tf){
    TextureMgr::Instance()->DrawFrame(tf, m_SpriteRow, m_CurrentFrame);
}

void SpritetAnimation::Update(){
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void SpritetAnimation::SetProps(int spriteRow, int frameCount, int speed){
    m_Speed = speed;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}
