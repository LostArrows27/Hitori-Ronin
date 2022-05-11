#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"
#include "ObjectFactory.h"

class Enemy: public GameObject {

    public:
        Enemy(Transform* tf);

        virtual void Draw();
        virtual void Update(float dt);

    private:
        Collider* m_Collider;
        RigidBody* m_RigiBody;
        SeqAnimation* m_Animation;
        Vector2D m_LastSafePosition;
};

#endif // ENEMY_H

