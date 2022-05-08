#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"

#include "Button.h"
#include "Frame.h"

Gui::Frame* frame1 = nullptr;

Menu::Menu(){}

bool Menu::Init(){
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    frame1 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
    Gui::Button* btn = new Gui::Button(Gui::Attr(m_Ctxt, 50, 50, 100, 35), StartGame);
    frame1->AddChild(btn);
    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Menu::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);

    frame1->Draw();
    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update(){
    frame1->Update();
}

bool Menu::Exit(){
    std::cout << "exit menu!" << std::endl;
    return true;
}

// Callbacks
void Menu::StartGame(){
    Engine::GetInstance()->ChangeState(new Play());
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


