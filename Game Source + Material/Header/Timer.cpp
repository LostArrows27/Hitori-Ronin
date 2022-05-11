#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

Timer::Timer(){
    m_LastTime = 0;
    m_DeltaTime = 0;
}

void Timer::Tick(){

    m_DeltaTime = (SDL_GetTicks() - m_LastTime)*FRAME_PER_SECOND;

    if(m_DeltaTime > MAX_DELTA_TIME)
        m_DeltaTime = MAX_DELTA_TIME;

    m_LastTime = SDL_GetTicks();

    SDL_Delay(FRAME_DELAY);
}
