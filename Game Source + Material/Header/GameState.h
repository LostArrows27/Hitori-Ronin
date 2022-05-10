#ifndef STATES_H
#define STATES_H

#include <SDL.h>
#include <iostream>

class GameState {

    public:
        virtual bool Init() = 0;
        virtual bool Exit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
         SDL_Renderer* m_Ctxt;
};

#endif // STATES_H
