#ifndef TIMER_H
#define TIMER_H

// fps of the game // 45 is the best fps but yah i found out 60 is more perfect to my game
// this time class handle time happen between 2 event
// like from keyboard, character
// u will see every update function in this have a "dt" component
// so that every 2 action cant take over "dt" time
// --> that remain fps of the game


const float FPS = 60.0f;
const float FRAME_PER_SECOND = FPS/1000.0f;

const float FRAME_DELAY = 1000.0f/FPS;
const float MAX_DELTA_TIME = 1.5f;

class Timer{

    public:
        void Tick(); // SDL already have "GetTick" function so yeah this name appear :D
        inline float GetDeltaTime(){return m_DeltaTime;}
        inline static Timer* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();}

    private:
         Timer();
         static Timer* s_Instance; //static cause the game can only have 1 time component
         float m_DeltaTime;
         float m_LastTime;
};

#endif // TIMER_H
