#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateMgr.h"

Menu::Menu(){}

bool Menu::Init(){
    m_Ctxt = Engine::Instance()->GetRenderer();

    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Menu::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);

    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update(){

}

bool Menu::Exit(){
    std::cout << "exit menu!" << std::endl;
    return true;
}

// Callbacks
void Menu::StartGame(){
    StateMgr::Instance()->ChangeState(new Play());
    std::cout << "start game!\n";
}

void Menu::Editor(){
    std::cout << "editor mode\n";
}

void Menu::Settings(){
    std::cout << "options mode\n";
}

void Menu::Quit(){
    std::cout << "quit game\n";
}


