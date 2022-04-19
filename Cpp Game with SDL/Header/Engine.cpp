#include "Engine.h"
#include "TextureManager.h"
#include "Transform.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG| IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initalize SDL: %s", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("The Lost Ronin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
    TextureManager::GetInstace()->Load("background", "Map/nightbg.png");

    Transform tf;
    tf.Log();
    return s_IsRunning = true;
}

bool Engine::Clean()
{
    TextureManager::GetInstace()->Clean();
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

}

void Engine::Render()
{
     SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
     SDL_RenderClear(m_Renderer);
     TextureManager::GetInstace()->Draw("background", 100, 100, 320, 180 );
     SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        Quit();
        break;
    }
}

