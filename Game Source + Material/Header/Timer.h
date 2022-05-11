#ifndef TIMER_H
#define TIMER_H

const float FPS = 60.0f;
const float FRAME_PER_SECOND = FPS/1000.0f;

const float FRAME_DELAY = 1000.0f/FPS;
const float MAX_DELTA_TIME = 1.5f;

class Timer{

    public:
        void Tick();
        inline float GetDeltaTime(){return m_DeltaTime;}
        inline static Timer* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();}

    private:
         Timer();
         static Timer* s_Instance;
         float m_DeltaTime;
         float m_LastTime;
};

#endif // TIMER_H
