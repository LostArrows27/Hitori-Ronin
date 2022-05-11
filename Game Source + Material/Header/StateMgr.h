#ifndef STATEMGR_H
#define STATEMGR_H

#include <vector>
#include "GameState.h"

#define SWITCH_DELAY 200

class StateMgr {

    public:
        void Render();
        void Update();

        void PopState();
        void PushState(GameState* current);
        void ChangeState(GameState* target);
        static StateMgr* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new StateMgr();}

    private:

        StateMgr(){}
        static StateMgr* s_Instance;
        std::vector<GameState*> m_GameStates;
};

#endif // STATEMGR_H
