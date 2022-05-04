#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collder.h"
#include "Vector2D.h"

#define JUMP_TIME 15.0f;
#define JUMP_FORCE 9.8f;

#define RUN_FORCE 3.8f
#define ATTACK_TIME 20.0f

class Warrior : public Character
{
    public:
        Warrior(Properties* props) ;

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsGrounded;
        bool m_IsFalling;
        bool m_IsAttacking1;
        bool m_IsAttacking2;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collder* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif // WARRIOR_H
