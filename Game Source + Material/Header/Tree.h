#ifndef TREE_H
#define TREE_H

#include "Helpers.h"
#include "GameObject.h"
#include "TextureMgr.h"
#include "ObjectFactory.h"

class Tree : public GameObject{

    public:
        Tree(Transform* tf):GameObject(tf) {
            TextureMgr::Instance()->QueryTexture(tf->TextureID, &m_Tf->Width, &m_Tf->Height);
        }

        virtual void Update(float dt) override {
            //m_CurrFrame = (Uint8)((SDL_GetTicks()/1000) % 2);
            //m_Tf->TextureID = (m_CurrFrame == 0)? "tree2" : "tree2";
        }
        // u can cmt this

    private:
        Uint8 m_CurrFrame;

};

static Registrar<Tree> tree("TREE");

#endif // TREE_H
