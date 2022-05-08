#include "SpriteAnimation.h"

SpritetAnimation::SpritetAnimation(bool repeat): Animation(repeat){}

void SpritetAnimation::Draw(float x, float y, int width, int height, SDL_RendererFlip flip, float scaleX, float scaleY, float rotation, float speedRatio){
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_CurrentFrame, flip, scaleX, scaleY, rotation, speedRatio);
}

void SpritetAnimation::Update(float dt){
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void SpritetAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed){
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}
