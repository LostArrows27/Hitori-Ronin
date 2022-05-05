#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>
#include "Camera.h"
#include "Enemy.h"
#include "ObjectFactory.h"

Engine* Engine::s_Instance = nullptr;


bool Engine::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG| IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initalize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("The Lost Ronin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr)
    {
        SDL_Log("Failed to Create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to Load map!!!" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMaps("MAP");

    TextureManager::GetInstace()->ParseTextures("Map/textures.tml");

    /*TextureManager::GetInstace()->Load("player", "Character/stay.png");
    TextureManager::GetInstace()->Load("player_run", "Character/run.png");
    TextureManager::GetInstace()->Load("Attack1", "Character/Attack1.png");
    TextureManager::GetInstace()->Load("Attack2", "Character/Attack2.png");
    TextureManager::GetInstace()->Load("bg", "Map/BG/newbg.png");
    TextureManager::GetInstace()->Load("jump", "Character/Jump.png");
    TextureManager::GetInstace()->Load("fall", "Character/Fall.png");*/


    //Warrior* player =  new Warrior(new Properties("player", 0, 0, 200, 200)); // 100 340 instead
    Properties* props = new Properties("player", 0, 0, 200, 200);

    GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    Enemy* boss = new Enemy(new Properties("BOSS", 500, 240, 460, 352));
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(boss);
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return s_IsRunning = true;
}

bool Engine::Clean()
{
    for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Clean();

    TextureManager::GetInstace()->Clean();
    MapParser::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    s_IsRunning = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();

    for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Update(dt);

    Camera::GetInstance() ->Update(dt);
    m_LevelMap->Update();
}

void Engine::Render()
{
     SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
     SDL_RenderClear(m_Renderer);

     TextureManager::GetInstace()->Draw("bg", 0, 0, 688, 127, 3, 3, 0.4);
     m_LevelMap->Render();

     for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();
     SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

