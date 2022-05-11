#include "Engine.h"
#include "assert.h"
#include "Play.h"
#include "Menu.h"
#include "StateMgr.h"

Engine* Engine::s_Instance = nullptr;

void Engine::Init(){
    srand (time(NULL));
    assert(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) && SDL_GetError());
    SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, w_flags);

    SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
    assert(m_Window && m_Renderer && SDL_GetError());

    m_ScreenViewPort = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    StateMgr::Instance()->ChangeState(new Menu());
   // StateMgr::Instance()->ChangeState(new Menu());
    m_IsRunning = true;
}

Engine::~Engine(){
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}





