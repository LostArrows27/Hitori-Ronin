#include "Pause.h"
#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateMgr.h"

Pause::Pause(){}

bool Pause::Init(){
    m_Ctxt = Engine::Instance()->GetRenderer();
    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Pause::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 211, 87, 85, 255);
    SDL_RenderClear(m_Ctxt);

    SDL_RenderPresent(m_Ctxt);
}

void Pause::Update(){

}

bool Pause::Exit(){
    std::cout << "exit menu!" << std::endl;
    return true;
}

// Callbacks
void Pause::Resume(){
    StateMgr::Instance()->PopState();
    std::cout << "resume game\n";
}


