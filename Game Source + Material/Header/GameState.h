#ifndef STATES_H
#define STATES_H

#include <iostream>
#include "ObjectFactory.h"

const SDL_Color ORANGE = {255, 177, 0};
const SDL_Color BLUE = {30, 191, 242};
const SDL_Color DARK = {45, 80, 82};

class GameState {

    public:
        virtual bool Init() = 0; // Tao component cua 1 state
        virtual bool Exit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;

    public:
        SDL_Renderer* m_Ctxt;
        // since every state will have it owns renderer
        SDL_Color m_BgColor;
};

#endif // STATES_H
