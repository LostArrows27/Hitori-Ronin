#include "Play.h"
#include "Menu.h"
#include "Pause.h"

#include "Frame.h"
#include "Button.h"
#include "Panel.h"
#include "Slider.h"

Play::Play(){}

bool Play::Init(){
    m_EditMode = false;
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->Parse("assets/textures.tml");
    m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetLayers().back();

    m_ParalaxBg.push_back(new ImgLayer("sky", 0, -50, 0.1, 3.0, 2.5));
    m_ParalaxBg.push_back(new ImgLayer("mountain", 0, 220, 0.2, 3.0, 2.5));

    m_ParalaxBg.push_back(new ImgLayer("cloud", 50, 60, 0.2));
    m_ParalaxBg.push_back(new ImgLayer("cloud", 1100, 60, 0.21));

    m_ParalaxBg.push_back(new ImgLayer("pine1", -10, 320, 0.3, 2.0, 2.0));
    m_ParalaxBg.push_back(new ImgLayer("pine1", 1366, 320, 0.3, 2.0, 2.0));

    m_ParalaxBg.push_back(new ImgLayer("pine2", -10, 400, 0.4, 2.0, 2.0));
    m_ParalaxBg.push_back(new ImgLayer("pine2", 1366, 400, 0.4, 2.0, 2.0));

    int tilesize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetWidth()*tilesize;
    int height = collisionLayer->GetHeight()*tilesize;

    Camera::GetInstance()->SetSceneLimit(width, height);
    CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(), tilesize);

    Warrior* warrior = new Warrior(new Properties(0, 0, 200, 200, "player_idle"));
    Camera::GetInstance()->SetTarget(warrior->GetOrigin());
    m_GameObjects.push_back(warrior);
    std::cout << "play initialized!" << std::endl;
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, 45, 80, 82, 255);
    SDL_RenderClear(m_Ctxt);

    for(auto imgLayer : m_ParalaxBg)
        imgLayer->Render();

    TextureManager::GetInstance()->Draw("tree", 100, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 400, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 600, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 800, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 1200, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 1500, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 1700, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 2000, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 2100, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 2800, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    TextureManager::GetInstance()->Draw("tree", 3300, 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    m_LevelMap->Render();

    for(auto gameobj : m_GameObjects)
        gameobj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();
    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){
    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    for(auto gameobj : m_GameObjects)
        gameobj->Update(dt);

    Camera::GetInstance()->Update();
    m_LevelMap->Update();
}

void Play::Events(){

    if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M))
        Engine::GetInstance()->ChangeState(new Menu());

    if(!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        m_EditMode = true;

    if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5))
        m_EditMode = false;
}

bool Play::Exit(){

    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto gameobj : m_GameObjects){
        gameobj->Clean();
        delete gameobj;
    }

    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    std::cout << "exit play" << std::endl;
    return true;
}

// callback action
void Play::OpenMenu(){
    Engine::GetInstance()->ChangeState(new Menu());
}

void Play::PauseGame(){
    Engine::GetInstance()->PushState(new Pause());
    std::cout << "pause game" << std::endl;
}


