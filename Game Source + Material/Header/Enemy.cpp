#include "Enemy.h"
#include "Input.h"
#include "CollisionMgr.h"
#include "ObjectFactory.h"
#include "SoundMgr.h"
#include "StateMgr.h"
#include "Menu.h"
#include "SDL.h"

static int stoplag = 1;

static Registrar<Enemy> enemy("ENEMY");

Enemy::Enemy(Transform* tf) : GameObject(tf){
    m_Tf->ScrollRatio = 1;
    m_AttackTime = 20.0f;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-85, -75, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SpritetAnimation();
    m_Animation->SetProps(1, 8, 100);
}

Enemy::~Enemy(){
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}

void Enemy::Draw(){
    //m_Collider->Draw();
    m_Animation->Draw(m_Tf);
}

void Enemy::Update(float dt){
    m_Tf->Flip = SDL_FLIP_HORIZONTAL;
    m_RigidBody->UnSetForce();
    //fall
    if(m_RigidBody->Veclocity().Y > 0){
        m_IsFalling = true;
        if(m_Collider->CollideWithMap()){
        m_IsFalling = false;
        m_RigidBody->UnSetForce();
        m_IsAttacking2 = true;
        }
    }

    // Attack timer
    if(m_IsAttacking1 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }else if(m_IsAttacking2 && m_AttackTime > 0){
        m_AttackTime -= dt;
    }else{
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
        m_AttackTime = 20.0f;
    }
    /*if(Engine::Instance()->can_fight1){
        m_IsDead = true;
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
    }*/



    // move on X axis
    m_RigidBody->Move(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 30, 50);

    if(m_Collider->CollideWithMap()){
        m_Tf->X = m_LastSafePosition.X;
        m_IsFalling = false;
        m_RigidBody->UnSetForce();
        m_IsAttacking1 = true;
    }

    // move on Y axis
    m_RigidBody->Move(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 30, 50);

    if(m_Collider->CollideWithMap()){
        m_Tf->Y = m_LastSafePosition.Y;
    }

   Animate();
   // m_Animation->Update(dt);
   GameObject::Update(dt);
}


void Enemy::Animate(){
    // idling
    m_Tf->TextureID = "player_idle";
    m_Animation->SetProps(0, 6, 150);

    if(m_IsDead){
        m_Tf->TextureID = "dead";
        m_Animation->SetProps(0, 6, 200);
    }
    // attacking
    if(m_IsAttacking1){
        m_Tf->TextureID = "player_attack1";
        m_Animation->SetProps(0, 6, 60);
    }

    //attacking2
    if(m_IsAttacking2){
        m_Tf->TextureID = "player_attack2";
        m_Animation->SetProps(0, 6, 90);
    }

    if(m_IsFalling){
        m_Tf->TextureID = "player_fall";
        m_Animation->SetProps(0, 2, 150);
    }


    m_Animation->Update();
}







