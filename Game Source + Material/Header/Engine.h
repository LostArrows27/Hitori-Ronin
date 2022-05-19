#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "GameState.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Gather everything in game together

class Engine {

    public:

        ~Engine();
        void Init();

        inline void Close(){m_IsRunning = false;}
        inline bool IsRunning(){return m_IsRunning;}

        inline SDL_Window* GetWindow(){return m_Window;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}

        inline SDL_Rect GetViewPort(){return m_ScreenViewPort;}
        inline void SetViewPort(SDL_Rect viewport){ m_ScreenViewPort = viewport;}

        inline static Engine* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();}
        bool m_IsRunning;
        int day_or_night = 1;
        bool can_fight1 = false;
        bool can_fight2 = false;
        bool can_fight3 = false;
        bool can_fight4 = false;

    private:
        Engine(){}
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Rect m_ScreenViewPort;
        // Based on window size
        // We have the update function to resize the viewport every time
        // the window resize
        // "WindowEvent" function in  "Input.h"
        static Engine* s_Instance;
};

#endif // ENGINE_H
