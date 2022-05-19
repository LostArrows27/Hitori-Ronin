#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "ObjectFactory.h"
#include "SoundMgr.h"
// since every state inherit from gamestate so each state has it owns renderer

class Menu : public GameState {

    public:
        Menu();
        ~Menu();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void StartGame();
        static void QuitGame();
        static void Settings();
        // 3 main function of our menu
        // but yeah i havent create the settting 1
        // deadline for sure T_T

    private:
        ObjectList m_GuiObjects;

};

#endif // MENU_H
