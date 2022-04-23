#include "Engine.h"
#include "Timer.h"
#include "TextureManager.h" // comment this

int main(int argc, char** argv)
{
    Engine::GetInstance()->init();
    while(Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
    return 0;
}

