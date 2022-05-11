/*#include "Button.h"
#include "Input.h"

namespace Ui{

    Button::Button(Vector2D offset, void (*click)()){
        m_Click = click;
        m_Container = new Panel(offset.X, offset.Y, 100, 35);
    }

    void Button::Show(){
        m_Container->Draw();
    }

    void Button::Refresh(){

        Vector2D mousePos = Input::Instance()->GetMousePosition();
        SDL_Point point = {mousePos.X, mousePos.Y};

        if(SDL_PointInRect(&point, &m_Container->Rect)){
            //clicked
            if(Input::Instance()->GetMouseButtonDown(LEFT) && m_IsReleased){
                m_IsReleased = false;
                m_Click();
            }
            //hover
            else if(!Input::Instance()->GetMouseButtonDown(LEFT)){
                m_IsReleased = true;
            }
        }
        // normal
        else{

        }
    }

    void Button::Destroy(){

    }


}*/
