#ifndef ENEMY_H
#define ENEMY_H

#include "RigidBody.h"
#include "Collider.h"
#include "GameObject.h"
#include "SpriteAnimation.h"


class Enemy: public GameObject{

    public:
        Enemy(Transform* tf);
        ~Enemy();

        virtual void Draw() override;
        virtual void Update(float dt) override;

        Collider* getRect() {return m_Collider;}
        //bool m_IsDead;

    private:
        void Animate();

    private:
        bool m_IsAttacking1;
        bool m_IsAttacking2;
        bool m_IsFalling;


        float m_AttackTime;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
        SpritetAnimation* m_Animation;
};

#endif // Enemy_H
