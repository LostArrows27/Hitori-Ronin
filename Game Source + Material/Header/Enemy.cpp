#include "Enemy.h"
#include "Camera.h"
#include "CollisionMgr.h"
#include <iostream>

static Registrar<Enemy> enemy("Enemy");

Enemy::Enemy(Transform* tf):GameObject(tf){

    m_RigiBody = new RigidBody();
    m_RigiBody->SetGravity(3.5);
    m_Collider = new Collider();

    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("assets/animations/boss/boss.aml");
    m_Animation->SetCurrentSeq("boss_appear");
}

void Enemy::Draw(){
    //m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Flip, 0.3f, 0.3f);
}

void Enemy::Update(float dt){

    // X-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigiBody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionMgr::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->X = m_LastSafePosition.X;

    // Y-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigiBody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionMgr::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->Y = m_LastSafePosition.Y;

    m_Animation->Update(dt);
    // u can cmt all "1" or put it in front of "Update" function
    if(m_Animation->IsEnded()){ // 1
        m_Animation->SetRepeat(true); // 1
        m_Animation->SetCurrentSeq("boss_idle"); // 1
    }
}


void Enemy::Clean(){

}



