#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "ObjectFactory.h"

class Menu : public GameState {

    public:
        Menu();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void StartGame();
        static void QuitGame();
        static void Settings();

    private:
        ObjectList m_GuiObjects;
};

#endif // MENU_H
