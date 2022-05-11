#include "Play.h"
#include "Menu.h"
#include "Pause.h"
#include "Helpers.h"
#include "Button.h"

enum DayTime {DAY=0, NIGHT};

Play::Play(){}

Play::~Play(){
    m_GameObjects.clear();
    m_GameObjects.shrink_to_fit();

    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();
}

bool Play::Init(){
    m_BgColor = DARK;
    m_Ctxt = Engine::Instance()->GetRenderer();

    Parser::Instance()->ParseSounds("assets/sounds.tml");
    Parser::Instance()->ParseTextures("assets/textures.tml");
    Parser::Instance()->ParseTextures("assets/ui_play.tml");
    m_TilelMap = Parser::Instance()->ParseMap("assets/maps/mymap.tmx");
    Parser::Instance()->ParseGameObjects("assets/levels/day.tml", &m_GameObjects);

    m_SceneClimat = new ClimatEmitter(DUST);
    TileLayer* layer = m_TilelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(layer);
    Camera::Instance()->SetMapLimit(layer->GetWidth(), layer->GetHeight());

    m_Player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(0, 0, 200, 200));
    Camera::Instance()->SetTarget(m_Player->GetOrigin());

    SoundMgr::Instance()->PlayMusik("onsen");

    Button* menubtn = new Button(10, 10, OpenMenu, {"home_n", "home_h", "home_p"});
    Button* pausebtn = new Button(70, 10, PauseGame, {"pause_n", "pause_h", "pause_p"});
    Button* optbtn = new Button(130, 10, Options, {"set_n", "set_h", "set_p"});

    m_GuiObjects.push_back(optbtn);
    m_GuiObjects.push_back(menubtn);
    m_GuiObjects.push_back(pausebtn);
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderClear(m_Ctxt);

    for(auto object : m_GameObjects)
        object->Draw();

    m_SceneClimat->RenderParticles();
    m_TilelMap->Render();
    m_Player->Draw();

    for(auto object : m_GuiObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();
    float dt = Timer::Instance()->GetDeltaTime();
    m_Player->Update(dt);

    Camera::Instance()->TrackTarget();

    m_TilelMap->Update();

    for(auto object : m_GameObjects)
        object->Update(dt);

    for(auto object : m_GuiObjects)
        object->Update(0);

    m_SceneClimat->UpdateParticles(dt);
}

void Play::Events(){
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        StateMgr::Instance()->ChangeState(new Menu());

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_P))
        StateMgr::Instance()->PushState(new Pause());

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_1))
        m_BgColor = ORANGE;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_2))
        m_BgColor = DARK;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_3))
        m_BgColor = BLUE;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_4))
        m_SceneClimat->InitParticles(RAIN);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_5))
        m_SceneClimat->InitParticles(SNOW);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_6))
        m_SceneClimat->InitParticles(DUST);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_7))
        m_SceneClimat->InitParticles(LIGTHNING);


}

bool Play::Exit(){
    SoundMgr::Instance()->Clean();
    TextureMgr::Instance()->Clean();
    return true;
}

void Play::OpenMenu(){
    StateMgr::Instance()->ChangeState(new Menu());
}

void Play::Options(){
    //StateMgr::Instance()->ChangeState(new Menu());
}

void Play::PauseGame(){
    StateMgr::Instance()->PushState(new Pause());
}



