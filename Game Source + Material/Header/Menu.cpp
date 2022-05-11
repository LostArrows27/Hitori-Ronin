#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateMgr.h"
#include "Button.h"
#include "ClimatEmitter.h"

Menu::Menu(){}

Menu::~Menu(){
    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();
}

bool Menu::Init(){
    m_BgColor = DARK;
    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/ui_menu.tml");

    Button* playbtn = new Button(250, 100, StartGame,{"play_n", "play_h", "play_p"});
    Button* settbtn = new Button(250, 250, Settings, {"opt_n", "opt_h", "opt_p"});
    Button* quitbtn = new Button(250, 400, QuitGame, {"quit_n", "quit_h", "quit_p"});

    m_GuiObjects.push_back(playbtn);
    m_GuiObjects.push_back(settbtn);
    m_GuiObjects.push_back(quitbtn);
    return true;
}

void Menu::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderClear(m_Ctxt);

    for(auto object : m_GuiObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update(){
    for(auto object : m_GuiObjects)
        object->Update(0);
}

bool Menu::Exit(){
    TextureMgr::Instance()->Clean();
    return true;
}

// Callbacks
void Menu::StartGame(){
    StateMgr::Instance()->ChangeState(new Play());
}

void Menu::Settings(){
    std::cout << "options settings\n";
}

void Menu::QuitGame(){
    Engine::Instance()->Close();
}


