#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt)
{
    if(m_Target != nullptr)
    {
        m_ViewBox.x = m_Target->X - SCREEN_WIDTH / 2;
        m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT / 2;

        if(m_ViewBox.x < 0)
        {
            m_ViewBox.x = 0;
        }

        if(m_ViewBox.y < 0)
        {
            m_ViewBox.y = 0;
        }

        if(m_ViewBox.x > (4.48*SCREEN_WIDTH - m_ViewBox.w)) // adjust this to the actual length you want to go far
        {
            m_ViewBox.x = (4.48*SCREEN_WIDTH - m_ViewBox.w); // this too map is 140*32 = 4480 length / 1000 screen length so ratio is 4.48
        }

        if(m_ViewBox.y > (SCREEN_HEIGHT - m_ViewBox.h))
        {
            m_ViewBox.y = (SCREEN_HEIGHT - m_ViewBox.h);
        }

        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}
