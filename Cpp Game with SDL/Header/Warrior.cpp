#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    //m_Row = 1;
    //m_FrameCount = 8;
    //m_AnimSpeed = 80;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 8, 80); // 80 la toc do cua chuyen dong
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player", 1 ,8 ,100);
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps("player_run", 1, 8, 100, SDL_FLIP_HORIZONTAL);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(5*FORWARD); // chinh toc do backward va forward de chinh toc do di chuyen
        m_Animation->SetProps("player_run", 1, 8, 100);
    }
    SDL_Log("%f", dt);
    m_RigidBody->Update(dt);
    //m_RigidBody->ApplyForceX(5); // roi cheo thay vi roi thang vi trong luc
    m_Transform->TranslateX(m_RigidBody->Position().X);
    //m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstace()->Clean();
}

