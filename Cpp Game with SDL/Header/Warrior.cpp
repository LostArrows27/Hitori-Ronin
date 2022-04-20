#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    //m_Row = 1;
    //m_FrameCount = 8;
    //m_AnimSpeed = 100;
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 8, 100, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstace()->Clean();
}

