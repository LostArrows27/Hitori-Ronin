#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateMgr.h"
#include "Button.h"
#include "ClimatEmitter.h"

Menu::Menu(){}

bool Menu::Init(){

    m_ClearColor = {16, 45, 70};
    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/gui_textures.tml");

    Button* playbtn = new Button(250, 100, StartGame,{"play_n", "play_h", "play_p"});
    Button* settbtn = new Button(250, 250, Settings, {"opt_n", "opt_h", "opt_p"});
    Button* quitbtn = new Button(250, 400, QuitGame, {"quit_n", "quit_h", "quit_p"});

    m_GuiObjects.push_back(playbtn);
    m_GuiObjects.push_back(settbtn);
    m_GuiObjects.push_back(quitbtn);

    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Menu::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
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
    m_GuiObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}

// Callbacks
void Menu::StartGame(){
    StateMgr::Instance()->ChangeState(new Play());
}

void Menu::Settings(){
    std::cout << "options mode\n";
}

void Menu::QuitGame(){
    Engine::Instance()->Close();
}


