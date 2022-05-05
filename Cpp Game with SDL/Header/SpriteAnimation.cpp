#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "SDL.h"

SpritetAnimation::SpritetAnimation(bool repeat): Animation(repeat){}

void SpritetAnimation::Draw(float x, float y, int width, int height, float xScale, float yScale){
    TextureManager::GetInstace()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_CurrentFrame, m_Flip);
}

void SpritetAnimation::Update(float dt){
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void SpritetAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed, SDL_RendererFlip flip){
    m_Flip = flip;
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}
