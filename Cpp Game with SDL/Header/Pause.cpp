#include "Pause.h"
#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"

#include "Button.h"
#include "Frame.h"

Gui::Frame* frame2 = nullptr;

Pause::Pause(){

}

bool Pause::Init(){
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    frame2 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
    Gui::Button* btn = new Gui::Button(Gui::Attr(m_Ctxt, 50, 50, 100, 35), Resume);
    frame2->AddChild(btn);
    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Pause::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 211, 87, 85, 255);
    SDL_RenderClear(m_Ctxt);

    frame2->Draw();
    SDL_RenderPresent(m_Ctxt);
}

void Pause::Update(){
    frame2->Update();
}

bool Pause::Exit(){
    std::cout << "exit menu!" << std::endl;
    return true;
}

// Callbacks
void Pause::Resume(){
    Engine::GetInstance()->PopState();
    std::cout << "resume game\n";
}


