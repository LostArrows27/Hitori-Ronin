#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

// gathering everything in game together

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }
        bool init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline GameMap* GetMap() {return m_LevelMap;}
        inline bool IsRunning() {return s_IsRunning;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}

    private:
        Engine() {}
        bool s_IsRunning;

        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
};

#endif // ENGINE_H