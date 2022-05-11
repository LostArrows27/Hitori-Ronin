#include "Enemy.h"
#include "Camera.h"
#include "CollisionMgr.h"
#include <iostream>

static Registrar<Enemy> enemy("ENEMY");

Enemy::Enemy(Transform* tf):GameObject(tf){

    m_RigiBody = new RigidBody();
    m_RigiBody->SetGravity(3.5);
    m_Collider = new Collider();

    m_Animation = new SeqAnimation();
    m_Animation->Parse("assets/animations/boss.aml");
    m_Animation->SetCurrSeq("boss_idle");
}

void Enemy::Draw(){
    m_Animation->Draw(m_Tf);
}

void Enemy::Update(float dt){

    // X-Axis movements
    m_RigiBody->Move(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigiBody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionMgr::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->X = m_LastSafePosition.X;

    // Y-Axis movements
    m_RigiBody->Move(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigiBody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionMgr::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->Y = m_LastSafePosition.Y;

    m_Animation->Update(m_Tf);
}



