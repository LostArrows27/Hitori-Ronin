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

const SDL_Color SKYBLUE = {30, 191, 242};
const SDL_Color SKYDARK = {45, 80, 82};

class Play : public GameState{

    public:
        Play();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        ObjectPtr m_Player;
        TileMap* m_LevelMap;
        SDL_Color m_ClearColor;
        ObjectList m_GameObjects;
};

#endif // PLAY_H
