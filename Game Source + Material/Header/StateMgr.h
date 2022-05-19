#ifndef STATEMGR_H
#define STATEMGR_H

#include <vector>
#include "GameState.h"

#define SWITCH_DELAY 200


// well the SWITCH_DELAY is why my game got a bit delay between any state

class StateMgr {

    public:
        void Render();
        void Update();

        void PopState(); // it was like you call a new state to the game and the prev 1 is still
        // like when you pause, your game standing still
        void PushState(GameState* current);
        // when you need to pop smth, you need to pushstate
        void ChangeState(GameState* target);
        static StateMgr* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new StateMgr();}

    private:

        StateMgr(){}
        static StateMgr* s_Instance;
        std::vector<GameState*> m_GameStates;
        // why vector ?
        // well, store all our state
};

#endif // STATEMGR_H
