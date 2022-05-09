#ifndef WARRIOR_H
#define WARRIOR_H

#include "RigidBody.h"
#include "Collider.h"
#include "GameObject.h"
#include "SpriteAnimation.h"

#define JUMP_FORCE 10.0f
#define JUMP_TIME 15.0f;

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior: public GameObject{

    public:
        Warrior(Transform* tf);
        virtual void Draw() override;
        virtual void Clean() override;
        virtual void Update(float dt) override;

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking1;
        bool m_IsAttacking2;
        bool m_IsCrouching;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
        SpritetAnimation* m_Animation;
};

#endif // WARRIOR_H
