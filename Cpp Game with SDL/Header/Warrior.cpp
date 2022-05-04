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
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collder();
    m_Collider->SetBuffer(-80, -60, 0, 0); // chinh 1 va 2 de vua vs design va khung cua nhan vat

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
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 124, 255, 0, 255);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box); // u can cmt this */

}

void Warrior::Update(float dt)
{
    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        state = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        state = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_RigidBody->UnSetForce();
        m_IsAttacking1 = true;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_RigidBody->UnSetForce();
        m_IsAttacking2 = true;
    }

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

    if(m_RigidBody->Velocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Attack timer
    if(m_IsAttacking1 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }else if(m_IsAttacking2 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }else{
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
        m_AttackTime = ATTACK_TIME;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 40, 60);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 40, 60);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    AnimationState();
    m_Animation->Update();



}

void Warrior::Clean()
{
    TextureManager::GetInstace()->Drop(m_TextureID);
}

void Warrior::AnimationState()
{
    m_Animation->SetProps("player", 1 ,8 ,100, state);
    if(m_IsRunning)
        m_Animation->SetProps("player_run", 1, 8, 100, state);
    if(m_IsJumping)
        m_Animation->SetProps("jump", 1, 2, 100, state);
    if(m_IsAttacking1)
        m_Animation->SetProps("Attack1", 1, 3, 80, state);
    if(m_IsAttacking2)
         m_Animation->SetProps("Attack2", 1, 6, 50, state);
    if(m_IsFalling)
        m_Animation->SetProps("fall", 1, 2, 150, state);

}

