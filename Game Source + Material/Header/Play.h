#ifndef PLAY_H
#define PLAY_H

#include <map>
#include <iostream>
#include "TileMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "Parser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "StateMgr.h"
#include "StaticObject.h"
#include "Cloud.h"
#include "ClimatEmitter.h"
#include "Tree.h"
#include "SoundMgr.h"
#include "Helpers.h"

class Play : public GameState {

    public:
        Play();
        ~Play();

        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();
         // level 1 is day level 2 is night

    private:
        static void OpenMenu();
        static void PauseGame();
        static void Options();

    private:
        ObjectPtr m_Enemy[4]; // if u create a certain enemy array but dont use all of them, they will point to somewhere else and cause crashing
        ObjectPtr m_Player;
        TileMap* m_TilelMap;
        ObjectList m_GuiObjects;
        ObjectList m_GameObjects;
        ClimatEmitter* m_SceneClimat;
};

#endif // PLAY_H
