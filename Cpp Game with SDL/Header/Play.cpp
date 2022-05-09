#include "Play.h"
#include "Menu.h"
#include "Pause.h"
#include "Helpers.h"

enum DayTime {DAY=0, NIGHT};
enum Weather {NORMAL=0, RAIN, SNOW, WIND, THUNDER};

Play::Play(){}

bool Play::Init(){

    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/textures.tml");
    m_LevelMap = Parser::Instance()->ParseMap("assets/maps/map.tmx");

    DayTime time = NIGHT;

    if(time == DAY)
        Parser::Instance()->ParseGameObjects("assets/day.tml", &m_GameObjects);
    else
        Parser::Instance()->ParseGameObjects("assets/night.tml", &m_GameObjects);

    TileLayer* colLayer = m_LevelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(colLayer);
    Camera::Instance()->SetMapLimit(colLayer->GetWidth(), colLayer->GetHeight());

    m_Player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(0, 0, 200, 200, "player_idle"));
    Camera::Instance()->SetTarget(m_Player->GetOrigin());

    std::cout << "play initialized!" << std::endl;
    return true;
}

void Play::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 45, 80, 82, 255);
    SDL_RenderClear(m_Ctxt);

    for(auto object : m_GameObjects)
        object->Draw();

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
}

void Play::Events(){
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        StateMgr::Instance()->ChangeState(new Menu());

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_P))
        StateMgr::Instance()->PushState(new Pause());
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



