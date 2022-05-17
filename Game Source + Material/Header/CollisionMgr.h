#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "TileMap.h"

class CollisionMgr{

    public:
        bool MapCollision(SDL_Rect a);
        bool isDead(SDL_Rect a);
        bool isWin(SDL_Rect a);
        int canAttack(SDL_Rect a);
        void NextLevel(SDL_Rect a);
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        void SetCollisionLayer(TileLayer* layer);

        inline static CollisionMgr* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionMgr();}
        void printMap(SDL_Rect a);


    private:
        CollisionMgr(){}

        int m_MapTileSize;
        int m_MapWidth, m_MapHeight;
        TileMatrix m_CollisionTilemap;
        static CollisionMgr* s_Instance;
};

#endif // COLLISIONHANDLER_H
