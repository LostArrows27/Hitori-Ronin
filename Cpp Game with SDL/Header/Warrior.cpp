#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Engine.h"

static SDL_RendererFlip state = SDL_FLIP_NONE;
// u can comment this "state" value if error to the youtube channel and remove all the "state" below :D

Warrior::Warrior(Properties* props) : Character(props)
{
    //m_Row = 1;
    //m_FrameCount = 8;
    //m_AnimSpeed = 80;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collder();
    m_Collider->SetBuffer(0, 80, 0, 0); // chinh 1 va 2 de vua vs design va khung cua nhan vat

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f); // u can change gravity here

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 8, 80); // 80 la toc do cua chuyen dong
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box); // u can cmt this

}

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player", 1 ,8 ,100, state);
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(5*BACKWARD);
        state = SDL_FLIP_HORIZONTAL;
        m_Animation->SetProps("player_run", 1, 8, 100, state);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(5*FORWARD); // chinh toc do backward va forward de chinh toc do di chuyen
        state = SDL_FLIP_NONE;
        m_Animation->SetProps("player_run", 1, 8, 100, state);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J))
    {
        m_RigidBody->ApplyForceX(0*BACKWARD);
        m_Animation->SetProps("Attack1", 1, 3, 80, state);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
    {
        m_RigidBody->ApplyForceX(0*BACKWARD);
        m_Animation->SetProps("Attack2", 1, 6, 50, state);
    }
    // jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 200, 200);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 200, 200);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }

    if(m_IsJumping || !m_IsGrounded){
        m_Animation->SetProps("jump", 1, 2, 150, state);
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstace()->Drop(m_TextureID);
}

