#include "Play.h"
#include "Menu.h"
#include "Pause.h"
#include "Helpers.h"
#include "Button.h"

enum DayTime {DAY=0, NIGHT};
ClimatEmitter* rEmttr = nullptr;

Play::Play(){}

bool Play::Init(){
    m_ClearColor = SKYBLUE;
    m_Ctxt = Engine::Instance()->GetRenderer();

    Parser::Instance()->ParseTextures("assets/textures.tml");
    m_TilelMap = Parser::Instance()->ParseMap("assets/maps/mymap.tmx");
    Parser::Instance()->ParseGameObjects("assets/levels/day.tml", &m_GameObjects);
    // u can change to dark later

    rEmttr = new ClimatEmitter(DUST);
    TileLayer* layer = m_TilelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(layer);
    Camera::Instance()->SetMapLimit(layer->GetWidth(), layer->GetHeight());

    m_Player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(0, 0, 200, 200));
    Camera::Instance()->SetTarget(m_Player->GetOrigin());

    Button* menubtn = new Button(100, 50, OpenMenu, {"home_n", "home_h", "home_p"});
    Button* optbtn = new Button(100, 50, Options, {"opt_n", "opt_h", "opt_p"});

    m_UiObjects.push_back(optbtn);
    m_UiObjects.push_back(menubtn);
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_Ctxt);

    for(auto object : m_GameObjects)
        object->Draw();

    rEmttr->RenderParticles();
    m_TilelMap->Render();
    m_Player->Draw();

    for(auto object : m_UiObjects)
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

    for(auto object : m_UiObjects)
        object->Update(0);

    rEmttr->UpdateParticles(dt);
}

void Play::Events(){
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        StateMgr::Instance()->ChangeState(new Menu());

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_P))
        StateMgr::Instance()->PushState(new Pause());

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_1))
        m_ClearColor = SKYDARK;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_2))
        m_ClearColor = SKYBLUE;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_3))
        rEmttr->InitParticles(RAIN);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_4))
        rEmttr->InitParticles(SNOW);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_5))
        rEmttr->InitParticles(DUST);
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_6))
        rEmttr->InitParticles(LIGTHNING);

}

bool Play::Exit(){
    m_GameObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}

void Play::OpenMenu(){
    std::cout << "open menu" << std::endl;
}

void Play::Options(){
    std::cout << "open option" << std::endl;
}



