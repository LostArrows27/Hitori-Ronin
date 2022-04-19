#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    m_Row = 1;
    m_FrameCount = 8;
    m_AnimSpeed = 100;
}

void Warrior::Draw()
{
    TextureManager::GetInstace()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Warrior::Update(float dt)
{
    m_Frame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Warrior::Clean()
{
    TextureManager::GetInstace()->Clean();
}

