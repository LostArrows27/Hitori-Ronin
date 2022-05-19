#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <vector>
#include "IObject.h"
#include "Transform.h"
#include "TextureMgr.h"

// ke thua tu "IObject"
// la class [Parent] cua tat ca object trong game tu tree, player, enemy, ....

class GameObject : public IObject {

    public:
        GameObject(Transform* tf): m_Tf(tf){}

        virtual void Draw(){
            TextureMgr::Instance()->Draw(m_Tf);
        }

        virtual void Update(float dt){
            m_Tf->Origin->X = m_Tf->X + m_Tf->Width/2;
            m_Tf->Origin->Y = m_Tf->Y + m_Tf->Height/2;
        }

        virtual void Clean(){}

        inline Vector2D* GetOrigin(){return m_Tf->Origin;}
        bool m_IsDead = false;
        float m_DeadTime;

    protected:
        Transform* m_Tf;

};

using ObjectPtr = GameObject*;
using ObjectList = std::vector<ObjectPtr>;

#endif // GAMEOBJECT_H
