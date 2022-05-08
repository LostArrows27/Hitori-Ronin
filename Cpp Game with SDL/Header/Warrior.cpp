#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "ObjectFactory.h"

static Registrar<Warrior> registrar("Warrior");

Warrior::Warrior(Properties* props):Character(props){
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-85, -68, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SpritetAnimation();
    m_Animation->SetProps(m_TextureID, 1, 8, 100); // sua
}

void Warrior::Draw(){
    //m_Collider->Draw();
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);
}

void Warrior::Update(float dt){

    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    // Run forward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    // Run backward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // Attack1
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_RigidBody->UnSetForce();
        m_IsAttacking1 = true;

    }

    // Attack2
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_RigidBody->UnSetForce();
        m_IsAttacking2 = true;
    }

    // Jump
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

    // Fall
    if(m_RigidBody->Veclocity().Y > 0 && !m_IsGrounded){
        m_IsFalling = true;
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
    }else
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

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 30, 50);

    if(m_Collider->CollideWithMap())
        m_Transform->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 30, 50);

    if(m_Collider->CollideWithMap()){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    AnimationState();
    m_Animation->Update(dt);
}


void Warrior::AnimationState(){
    // idling
    m_Animation->SetProps("player_idle", 0, 8, 100);

    // running
    if(m_IsRunning)
        m_Animation->SetProps("player_run", 0, 8, 100);

    // jumping
    if(m_IsJumping)
         m_Animation->SetProps("player_jump", 0, 2, 200);

    // falling
    if(m_IsFalling)
         m_Animation->SetProps("player_fall", 0, 2, 150);

    // attacking
    if(m_IsAttacking1)
        m_Animation->SetProps("player_attack1", 0, 6, 60);

    // attacking2
    if(m_IsAttacking2)
        m_Animation->SetProps("player_attack2", 0, 6, 60);

}

void Warrior::Clean(){

}

