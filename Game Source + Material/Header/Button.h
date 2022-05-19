#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include <string>
#include <vector>
#include "Input.h"
#include "GameObject.h"
#include "TextureMgr.h"

// class "Inherit" from "GameObject"

using TextureIdList = std::vector<std::string>;

enum ButtonState {NORMAL=0, HOVER=1, PRESSED=2};
// NORMAL : havent clicked
// HOVER : moving your mouse to the area of the button
// PRESSED: your mouse pressed the button

class Button : public GameObject {

    public:

        Button(int x, int y, void (*callback)(), TextureIdList textrIDs):GameObject(new Transform()){
            m_Tf->X = x;
            m_Tf->Y = y;
            m_Callback = callback;
            m_TextrIDs = textrIDs;
            m_Tf->TextureID = m_TextrIDs[NORMAL];
            TextureMgr::Instance()->QueryTexture(m_Tf->TextureID, &m_Tf->Width, &m_Tf->Height);
            m_Shape = {m_Tf->X, m_Tf->Y, m_Tf->Width, m_Tf->Height};
        }

        ~Button(){
            m_TextrIDs.clear();
            m_TextrIDs.shrink_to_fit();
        }

        virtual void Clean() override{
            for(auto id : m_TextrIDs)
                TextureMgr::Instance()->DestroyTexture(id);
            m_TextrIDs.clear();
            m_TextrIDs.shrink_to_fit();
            // set size cua vector ve 0 trong truong hop mo menu 3, 4 lan
            // so that you dont have to create new one
            // and reuse the old 1
        }

        virtual void Update(float dt) override {
            Vector2D mPos = Input::Instance()->GetMousePosition();
            SDL_Point point = {mPos.X, mPos.Y};

            if(SDL_PointInRect(&point, &m_Shape)){
                if(Input::Instance()->GetMouseButtonDown(LEFT) && m_IsReleased){
                    m_Callback();
                    m_IsReleased = false;
                    m_Tf->TextureID = m_TextrIDs[PRESSED];
                }
                else if(!Input::Instance()->GetMouseButtonDown(LEFT)){
                    m_IsReleased = true;
                    m_Tf->TextureID = m_TextrIDs[HOVER];
                }
            }
            else{
                m_Tf->TextureID = m_TextrIDs[NORMAL];
            }
        }

    private:
        SDL_Rect m_Shape; // vi tri and thong so "Button"
        bool m_IsReleased; // as we know the button alwasy render as in "NORMAL" state
        void (*m_Callback)();
        TextureIdList m_TextrIDs; // vector keep all the "TextureID"
};

#endif // BUTTON_H
