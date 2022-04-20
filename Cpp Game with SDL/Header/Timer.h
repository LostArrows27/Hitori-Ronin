#ifndef TIMER_H
#define TIMER_H

// for handling fps and time between 2 event from keyboard

const int TARGET_FPS = 45; // fps of the game // 60 is the best fpt but yah i found out 45 is more perfect to my game
const float TARGET_DELTATIME = 1.5f;

class Timer
{
    public:
        void Tick();
        inline float GetDeltaTime() {return m_DeltaTime;}
        inline static Timer* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();
        }


    private:
        Timer(){}
        static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;

};

#endif // TIMER_H
