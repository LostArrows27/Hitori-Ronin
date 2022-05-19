#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include "Helpers.h"
#include "Engine.h"
#include "Vector2D.h"
#include "TextureMgr.h"

// "Particle" which mean "Hat nho"
// well this class will render 1 so luong nhat dinh nhung particle
// each particle fall out of screen (up, down,.. ) will be destroy so that memory dont leak
// each of its will have a lifetime too


class Particle {

    public:

        Particle(Transform tf, Vector2D vel, Uint32 lifeTime){
            m_Vel = vel;
            m_Tf.X = tf.X; m_Tf.Y = tf.Y;
            m_Tf.TextureID = tf.TextureID;
            m_LifeTime = (SDL_GetTicks() + lifeTime);
            TextureMgr::Instance()->QueryTexture(tf.TextureID, &m_Tf.Width, &m_Tf.Height);
        }

        virtual void Show(){
            TextureMgr::Instance()->Draw(&m_Tf);
        }

        virtual void Move(float dt){
             m_Tf.X += m_Vel.X*dt;
             m_Tf.Y += m_Vel.Y*dt;
        }

        virtual bool IsDead(){
            const SDL_Rect vp = Engine::Instance()->GetViewPort();
            // render particle dua theo vi tri cua nhan vat
            // tranh hien tuong chi render o 1 vung when character is moving
            // trong truong hop resize man hinh thi bui se resize theo
            return ((SDL_GetTicks() >= m_LifeTime) || (m_Tf.X < 0) || (m_Tf.Y < 0) || (m_Tf.X > vp.w) || (m_Tf.Y > vp.h));
        }

    private:
        Vector2D m_Vel;
        Transform m_Tf;
        Uint32 m_LifeTime; // this lifetime will save your memory:D
        // why Uint 32. hmm, cause your lifetime cant < 0
        float m_xVel, m_yVel;
};

#endif // PARTICLE_H
