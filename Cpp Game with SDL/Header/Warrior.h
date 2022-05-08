#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collder.h"
#include "Vector2D.h"

class Warrior: public Character{

    public:
        Warrior(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking1;
        bool m_IsAttacking2;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        SpritetAnimation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif // WARRIOR_H
