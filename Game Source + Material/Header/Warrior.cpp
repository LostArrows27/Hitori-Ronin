#include "Warrior.h"
#include "Input.h"
#include "CollisionMgr.h"
#include "ObjectFactory.h"

static Registrar<Warrior> warrior("WARRIOR");

Warrior::Warrior(Transform* tf) : GameObject(tf){
    m_Tf->ScrollRatio = 1;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-85, -75, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SpritetAnimation();
    m_Animation->SetProps(1, 8, 100);
}

void Warrior::Draw(){
    //m_Collider->Draw();
    m_Animation->Draw(m_Tf);
}

void Warrior::Update(float dt){

    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    // Run forward
    if(Input::Instance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    // Run backward
    if(Input::Instance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking1 && !m_IsAttacking2){
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // Attack1
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_K)){
        m_RigidBody->UnSetForce();
        m_IsAttacking1 = true;
    }

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_L)){
        m_RigidBody->UnSetForce();
        m_IsAttacking2 = true;
    }

    // Jump
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Fall
    if(m_RigidBody->Veclocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Attack timer
    if(m_IsAttacking1 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }else if(m_IsAttacking2 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }
    else{
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
        m_AttackTime = ATTACK_TIME;
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 30, 50);

    if(m_Collider->CollideWithMap())
        m_Tf->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 30, 50);

    if(m_Collider->CollideWithMap()){
        m_IsGrounded = true;
        m_Tf->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }

    GameObject::Update(dt);

    AnimationState();
    m_Animation->Update(dt);
}


void Warrior::AnimationState(){
    // idling
    m_Tf->TextureID = "player_idle";
    m_Animation->SetProps(0, 6, 100);

    // running
    if(m_IsRunning){
        m_Tf->TextureID = "player_run";
        m_Animation->SetProps(0, 8, 100);
    }

    // jumping
    if(m_IsJumping){
        m_Tf->TextureID = "player_jump";
        m_Animation->SetProps(0, 2, 200);
    }

    // falling
    if(m_IsFalling){
        m_Tf->TextureID = "player_fall";
        m_Animation->SetProps(0, 2, 150);
    }

    // attacking
    if(m_IsAttacking1){
        m_Tf->TextureID = "player_attack1";
        m_Animation->SetProps(0, 6, 60);
    }

    //attacking2
    if(m_IsAttacking2){
        m_Tf->TextureID = "player_attack2";
        m_Animation->SetProps(0, 6, 60);
    }
}

void Warrior::Clean(){

}

