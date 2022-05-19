#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

Timer::Timer(){
    m_LastTime = 0;
    m_DeltaTime = 0;
}

void Timer::Tick(){

    m_DeltaTime = (SDL_GetTicks() - m_LastTime)*FRAME_PER_SECOND;
    // Deltatime la thoi gian giua 2 hanh dong trong game
    // like when you move 2 frame of character running

    if(m_DeltaTime > MAX_DELTA_TIME)
        m_DeltaTime = MAX_DELTA_TIME;

    m_LastTime = SDL_GetTicks();
    // we make lastTime = gettick so next time, time between 2 action can be calculate

    SDL_Delay(FRAME_DELAY);
}
