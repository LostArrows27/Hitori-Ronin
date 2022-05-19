#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1


class RigidBody {

    public:
        RigidBody() {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
        }

        // Setter Gravity & Mass
        inline void SetMass(float mass){m_Mass = mass;}
        inline void SetGravity(float gravity){m_Gravity = gravity;}

        // Force
        inline void ApplyForce(Vector2D F){m_Force = F;}
        inline void ApplyForceX(float Fx){m_Force.X = Fx;}
        inline void ApplyForceY(float Fy){m_Force.Y = Fy;}
        inline void UnSetForce(){m_Force = Vector2D(0,0);}
        // well this mean like your character wont have any x or y force so he stays still

        // Friction
        inline void ApplyFriction(Vector2D Fr){m_Friction = Fr;}
        inline void UnSetFriction(){m_Friction = Vector2D(0,0);}

        // Getters
        inline float GetMass(){return m_Mass;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Veclocity(){return m_Velocity;}
        inline Vector2D Accelaration(){return m_Accelaration;}


        // update methode
        void Move(float dt){
            m_Accelaration.X = (m_Force.X + m_Friction.X)/m_Mass;
            // force + friction = mass * acceralation
            m_Accelaration.Y = m_Gravity + m_Force.Y/m_Mass;
            // force + gravity = mass * acc
            // well, we need mass because this the force will pull player down when he jumping
            m_Velocity = m_Accelaration*dt;
            // v = a * t (vector2d * const)
            m_Position = m_Velocity*dt;
            // s = v * t
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        // move your position based on x or y axis
        // x axis: when player running
        // y axis: when player jumping
        Vector2D m_Friction; // "ma sat" when ever player walking on ice, swimming or what ever
        // but my game simply player walking on ground so yeah not really need this

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Accelaration;

};

#endif // RIGIDBODY_H
