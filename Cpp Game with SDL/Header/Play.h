#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include "TileMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "ImgLayer.h"

class Play : public GameState{

    public:
        Play();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        bool m_EditMode;
        TileMap* m_LevelMap;
        std::vector<ImgLayer*>  m_ParalaxBg;
        std::vector<GameObject*> m_GameObjects;
};

#endif // PLAY_H
