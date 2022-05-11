#include "Pause.h"
#include "Menu.h"
#include "Play.h"
#include "Input.h"
#include "Engine.h"
#include "StateMgr.h"
#include "Button.h"

Pause::Pause(){}

Pause::~Pause(){
    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();
}

bool Pause::Init(){
    m_BgColor = ORANGE;
    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/ui_pause.tml");

    Button* resbtn = new Button(150, 100, Resume,{"left_n", "left_h", "left_p"});
    Button* optbtn = new Button(250, 100, OpenMenu, {"home_n", "home_h", "home_p"});
    Button* menubtn = new Button(350,100, Options, {"set_n", "set_h", "set_p"});

    m_GuiObjects.push_back(resbtn);
    m_GuiObjects.push_back(menubtn);
    m_GuiObjects.push_back(optbtn);
    return true;
}

void Pause::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderClear(m_Ctxt);

    TextureMgr::Instance()->Draw(new Transform(600, 50, 500, 200, "pause"));

    SDL_SetRenderDrawBlendMode(m_Ctxt, SDL_BLENDMODE_MOD);
     for(auto object : m_GuiObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Pause::Update(){
    for(auto object : m_GuiObjects)
        object->Update(0);
}

bool Pause::Exit(){
    //TextureMgr::Instance()->Clean();
    return true;
}

// Callbacks
void Pause::Resume(){
    StateMgr::Instance()->PopState();
}

void Pause::Options(){
    //StateMgr::Instance()->PopState();
}

void Pause::OpenMenu(){
    StateMgr::Instance()->ChangeState(new Menu());
}



