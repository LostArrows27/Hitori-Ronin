#include "Engine.h"
#include "Timer.h"
#include "Input.h"
#include "StateMgr.h"

int main(int argc, char** argv){

    Engine::Instance()->Init();

    while(Engine::Instance()->IsRunning()){
        Input::Instance()->Listen();
        StateMgr::Instance()->Render();
        StateMgr::Instance()->Update();
        Timer::Instance()->Tick();
    }

    return EXIT_SUCCESS;
}
