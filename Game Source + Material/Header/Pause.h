#ifndef PAUSE_H
#define PAUSE_H

#include "GameState.h"

class Pause: public GameState {

    public:
        Pause();
        ~Pause();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void Resume();
        static void Options();
        static void OpenMenu();

    private:
        ObjectList m_GuiObjects;
};

#endif // PAUSE_H
