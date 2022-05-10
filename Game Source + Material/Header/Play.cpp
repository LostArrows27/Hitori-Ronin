#include "Play.h"
#include "Menu.h"
#include "Pause.h"
#include "Helpers.h"

enum DayTime {DAY=0, NIGHT};
ClimatEmitter* rEmttr = nullptr;
ClimatEmitter* lightEmttr = nullptr;

Play::Play(){}

bool Play::Init(){
    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/textures.tml");
    m_LevelMap = Parser::Instance()->ParseMap("assets/maps/mymap.tmx");

    if(Helpers::RandI(0,10) <= 5){
        Parser::Instance()->ParseGameObjects("assets/day.tml", &m_GameObjects);
        m_ClearColor = SKYBLUE;
    }else{
        Parser::Instance()->ParseGameObjects("assets/night.tml", &m_GameObjects);
        m_ClearColor = SKYDARK;
    }

    //m_CurrClimat = (Climat)Helpers::RandI(0, 3);
    rEmttr = new ClimatEmitter(DUST);
    // u can press from 1- 6 to change climate and sky state
    // for more infor go to the void event down belown


    TileLayer* colLayer = m_LevelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(colLayer);
    Camera::Instance()->SetMapLimit(colLayer->GetWidth(), colLayer->GetHeight());

    Transform* tf = new Transform(0, 0, 200, 200, "", SDL_FLIP_NONE, 1.0f, 1.0f, 1.0f, 1.0f);
    m_Player = ObjectFactory::Instance()->CreateObject("WARRIOR", tf);
    Camera::Instance()->SetTarget(m_Player->GetOrigin());

    std::cout << "play initialized!" << std::endl;
    return true;
}

void Play::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 255);
    SDL_RenderClear(m_Ctxt);

    for(auto object : m_GameObjects)
        object->Draw();

    rEmttr->RenderParticles();
    m_LevelMap->Render();
    m_Player->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();

    float dt = Timer::Instance()->GetDeltaTime();
    m_Player->Update(dt);

    Camera::Instance()->TrackTarget();

    m_LevelMap->Update();

    for(auto object : m_GameObjects)
        object->Update(dt);

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

    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto object : m_GameObjects){
        object->Clean();
        delete object;
    }

    m_GameObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}



