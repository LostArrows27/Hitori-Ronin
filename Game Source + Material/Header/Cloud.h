#ifndef CLOUD_H
#define CLOUD_H

#include <SDL.h>
#include "Engine.h"
#include "Helpers.h"
#include "GameObject.h"
#include "TextureMgr.h"
#include "ObjectFactory.h"

#define MAX_COUNTER 30
#define MIN_COUNTER 10

// speed of the cloud

class Cloud : public GameObject {

    public:
        Cloud(Transform* tf): GameObject(tf){
            TextureMgr::Instance()->QueryTexture(tf->TextureID, &m_Tf->Width, &m_Tf->Height);
            // since Cloud inherit from Gameobject so tf and m_Tf is the same thing
            m_Counter = m_CounterMaxValue = Helpers::RandI(MIN_COUNTER, MAX_COUNTER);
        }

        virtual void Update(float dt) override {
            m_Counter -= dt;
            if(m_Counter <= 0){
                m_Tf->X--;
                const SDL_Rect viewport = Engine::Instance()->GetViewPort();
                int topLeft = m_Tf->X + (m_Tf->Width*m_Tf->ScaleX);

                if(topLeft < viewport.x)
                    m_Tf->X = viewport.w;
                // it was like your part which go out side of the screen go back to the left
                // like in snake game i guess:D

                m_Counter = m_CounterMaxValue;
            }
        }

    private:
        int m_Counter;
        int m_CounterMaxValue;
};

static Registrar<Cloud> cloud("CLOUD");

#endif // CLOUD_H
