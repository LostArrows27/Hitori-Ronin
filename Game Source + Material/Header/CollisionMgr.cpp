#include "CollisionMgr.h"
#include "Engine.h"
#include "Play.h"
#include "Menu.h"

static int counting = 1;


CollisionMgr* CollisionMgr::s_Instance = nullptr;

void CollisionMgr::SetCollisionLayer(TileLayer* layer){
    m_CollisionTilemap = layer->GetTileMap();
    m_MapTileSize = layer->GetTileSize();
    m_MapHeight = layer->GetWidth();
    m_MapWidth = layer->GetHeight();
}

bool CollisionMgr::CheckCollision(SDL_Rect a, SDL_Rect b){
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionMgr::MapCollision(SDL_Rect a){

    int left_tile = a.x/m_MapTileSize;
    int right_tile = (a.x + a.w)/m_MapTileSize;

    int top_tile = a.y/m_MapTileSize;
    int bottom_tile = (a.y + a.h)/m_MapTileSize;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > m_MapWidth) right_tile = m_MapWidth;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > m_MapHeight) bottom_tile = m_MapHeight;
    for(int i = left_tile; i <= right_tile; ++i){
        for(int j = top_tile; j <= bottom_tile; ++j){
            if(m_CollisionTilemap[j][i] > 0){
                return true;
            }
        }
    }
    return false;
}

void CollisionMgr::NextLevel(SDL_Rect a){
    int left_tile = a.x/m_MapTileSize;
    int right_tile = (a.x + a.w)/m_MapTileSize;

    int top_tile = a.y/m_MapTileSize;
    int bottom_tile = (a.y + a.h)/m_MapTileSize;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > m_MapWidth) right_tile = m_MapWidth;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > m_MapHeight) bottom_tile = m_MapHeight;
    if(right_tile = 120 && left_tile == 119 && top_tile == 16 && bottom_tile == 18){
        Engine::Instance()->day_or_night = 2;
        StateMgr::Instance()->ChangeState(new Menu());
        SoundMgr::Instance()->PlayEffect("victory");
    }
}

bool CollisionMgr::isDead(SDL_Rect a){
    int left_tile = a.x/m_MapTileSize;
    int right_tile = (a.x + a.w)/m_MapTileSize;

    int top_tile = a.y/m_MapTileSize;
    int bottom_tile = (a.y + a.h)/m_MapTileSize;
    if(left_tile < 0) left_tile = 0;
    if(right_tile > m_MapWidth) right_tile = m_MapWidth;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > m_MapHeight) bottom_tile = m_MapHeight;
    for(int i = left_tile; i <= right_tile; ++i){
        for(int j = top_tile; j <= bottom_tile; ++j){
            if(m_CollisionTilemap[j][i] == 160){
                return true;
            }
        }
    }
    for(int i = left_tile; i <= right_tile; ++i){
        for(int j = top_tile; j <= bottom_tile; ++j){
            if(j == 20 && (((i == 19 && !Engine::Instance()->can_fight1)) || ((i == 46 && !Engine::Instance()->can_fight2)) || ((i == 67 && !Engine::Instance()->can_fight3)) || ((i == 83 && !Engine::Instance()->can_fight4 )))){
                return true;
            }
        }
    }
    return false;
}
void CollisionMgr::printMap(SDL_Rect a)
{
    int left_tile = a.x/m_MapTileSize;
    int right_tile = (a.x + a.w)/m_MapTileSize;

    int top_tile = a.y/m_MapTileSize;
    int bottom_tile = (a.y + a.h)/m_MapTileSize;
    if(left_tile < 0) left_tile = 0;
    if(right_tile > m_MapWidth) right_tile = m_MapWidth;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > m_MapHeight) bottom_tile = m_MapHeight;
        std::cout << left_tile << " " << right_tile << " " << top_tile << " " << bottom_tile << std::endl;
}

int CollisionMgr::canAttack(SDL_Rect a)
{
    int left_tile = a.x/m_MapTileSize;
    int right_tile = (a.x + a.w)/m_MapTileSize;

    int top_tile = a.y/m_MapTileSize;
    int bottom_tile = (a.y + a.h)/m_MapTileSize;
    if(left_tile < 0) left_tile = 0;
    if(right_tile > m_MapWidth) right_tile = m_MapWidth;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > m_MapHeight) bottom_tile = m_MapHeight;
    for(int i = left_tile; i <= right_tile; ++i){
        for(int j = top_tile; j <= bottom_tile; ++j){
            if(j == 20 && (i >= 21 && i <= 24)) return 1;
            if(j == 20 && (i >= 47 && i <= 50)) return 2;
            if(j == 20 && (i >= 67 && i <= 72)) return 3;
            if(j == 20 && (i >= 83 && i <= 87)) return 4;
        }
    }
    return 0;
}










