#include "Play.h"
#include "Menu.h"
#include "Pause.h"
#include "Helpers.h"
#include "Button.h"
#include "CollisionMgr.h"

enum DayTime {DAY=0, NIGHT};

int MAX_ENEMY = 3;

Play::Play(){}

Play::~Play(){
    m_GameObjects.clear();
    m_GameObjects.shrink_to_fit();

    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();
}

bool Play::Init(){
    if(Engine::Instance()->day_or_night == 1){
        m_BgColor = BLUE;

    }else{
        m_BgColor = DARK;
    }
    m_Ctxt = Engine::Instance()->GetRenderer();

    Parser::Instance()->ParseSounds("assets/sounds.tml");
    SoundMgr::Instance()->PlayMusik("japan2");
    Parser::Instance()->ParseTextures("assets/textures.tml");
    Parser::Instance()->ParseTextures("assets/ui_play.tml");
    m_TilelMap = Parser::Instance()->ParseMap("assets/maps/mymap.tmx");
    if(Engine::Instance()->day_or_night == 1){
        Parser::Instance()->ParseGameObjects("assets/levels/day.tml", &m_GameObjects);
        m_SceneClimat = new ClimatEmitter(DUST);
    }else{
        Engine::Instance()->can_fight1 = false;
        Engine::Instance()->can_fight2 = false;
        Engine::Instance()->can_fight3 = false;
        Engine::Instance()->can_fight4 = false;
        Parser::Instance()->ParseGameObjects("assets/levels/night.tml", &m_GameObjects);
        m_SceneClimat = new ClimatEmitter(RAIN);
    }
    // this day or night tml file will be a parralax BG
    // which is a bg with many layer
    // each layer have it owns scroll ratio
    // scrollratio = 1, mean it move with the same speed as the player move

    // well this is like create new level
    // since "deadline" so yeah i just set the 2 level just the same
    // but the weather and day - night state will change

    TileLayer* layer = m_TilelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(layer);
    Camera::Instance()->SetMapLimit(layer->GetWidth(), layer->GetHeight());
    // and yeah the camera take it limit from all the number above
    m_Player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(0, 0, 200, 200));
    m_Enemy[0] = ObjectFactory::Instance()->CreateObject("ENEMY", new Transform(600, 0, 200, 200));
    m_Enemy[1] = ObjectFactory::Instance()->CreateObject("ENEMY", new Transform(1481, 0, 200, 200));
    m_Enemy[2] = ObjectFactory::Instance()->CreateObject("ENEMY", new Transform(2118, 0, 200, 200));
    m_Enemy[3] = ObjectFactory::Instance()->CreateObject("ENEMY", new Transform(2667, 0, 200, 200));


    Camera::Instance()->SetTarget(m_Player->GetOrigin());
    // get origin based on the character you just create above
    if(Engine::Instance()->day_or_night == 1){
        SoundMgr::Instance()->PlayMusik("japan1");
    }else{
        SoundMgr::Instance()->PlayMusik("japan2");
    }

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
    if(Engine::Instance()->can_fight1 != true) m_Enemy[0]->Draw();
    else m_Enemy[0]->Clean();
    if(Engine::Instance()->can_fight2 != true) m_Enemy[1]->Draw();
    else m_Enemy[1]->Clean();
    if(Engine::Instance()->can_fight3 != true) m_Enemy[2]->Draw();
    else m_Enemy[2]->Clean();
    if(Engine::Instance()->can_fight4 != true) m_Enemy[3]->Draw();
    else m_Enemy[3]->Clean();

    for(auto object : m_GuiObjects)
        object->Draw();
    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){
    Events();
    float dt = Timer::Instance()->GetDeltaTime();
    if(m_Player->m_DeadTime >= 0) m_Player->Update(dt);
    if(Engine::Instance()->can_fight1 != true) m_Enemy[0]->Update(dt);
    if(Engine::Instance()->can_fight2 != true) m_Enemy[1]->Update(dt);
    if(Engine::Instance()->can_fight3 != true) m_Enemy[2]->Update(dt);
    if(Engine::Instance()->can_fight4 != true) m_Enemy[3]->Update(dt);
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
    StateMgr::Instance()->ChangeState(new Menu());
}

void Play::PauseGame(){
    StateMgr::Instance()->PushState(new Pause());
}



