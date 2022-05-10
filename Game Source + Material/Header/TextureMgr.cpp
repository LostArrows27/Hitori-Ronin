#include "TextureMgr.h"
#include "Engine.h"
#include "Camera.h"
#include "tinyxml.h"
#include <iostream>

TextureMgr* TextureMgr::s_Instance = nullptr;

SDL_Texture* TextureMgr::Load(std::string filename){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        std::cout << "IMG_Load Failed: " << filename << " " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Instance()->GetRenderer(), surface);
    if(texture == nullptr){
        std::cout << "Failed to create surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

bool TextureMgr::Add(std::string id, std::string filename){

    if(m_TextureMap.count(id) > 0){
        std::cout << "Texture id: " << id << " already exist in map" << std::endl;
        return false;
    }
    else{
        SDL_Texture* texture = Load(filename);
        if(texture == nullptr){
            std::cout << "Texture id: "<< id << " is empty" << std::endl;
            return false;
        }
        m_TextureMap[id] = texture;
    }
    return true;
}

void TextureMgr::Draw(Transform* tf){

    const Vector2D cam = Camera::Instance()->GetPosition()*tf->ScrollRatio;
    const SDL_Rect dstRect = {tf->X - cam.X, tf->Y - cam.Y, tf->Width*tf->ScaleX, tf->Height*tf->ScaleY};

    if(Camera::Instance()->GetInsectionWithViewPort(&dstRect)){
        const SDL_Rect srcRect = {0, 0, tf->Width, tf->Height};
        SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, tf->Rotation, nullptr, tf->Flip);
    }
}

void TextureMgr::DrawFrame(Transform* tf, int row, int frame){
    const Vector2D cam = Camera::Instance()->GetPosition()*tf->ScrollRatio;
    const SDL_Rect dstRect = {tf->X - cam.X, tf->Y - cam.Y, tf->Width*tf->ScaleX, tf->Height*tf->ScaleY};

    if(Camera::Instance()->GetInsectionWithViewPort(&dstRect)){
        const SDL_Rect srcRect = {tf->Width*frame, tf->Height*row, tf->Width, tf->Height};
        SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, tf->Rotation, nullptr, tf->Flip);
    }
}

void TextureMgr::DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio){

    Vector2D cam = Camera::Instance()->GetPosition()*speedRatio;
    const SDL_Rect dstRect = {x - cam.X, y - cam.Y, tilesize, tilesize};

    if(Camera::Instance()->GetInsectionWithViewPort(&dstRect)){
        SDL_Rect srcRect = {tilesize*col, tilesize*row, tilesize, tilesize};
        SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void TextureMgr::QueryTexture(std::string id, int* out_w, int* out_h){
    SDL_QueryTexture(m_TextureMap[id], NULL, NULL, out_w, out_h);
}

void TextureMgr::Clean(){
    for(TextureMap::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
    std::cout << "Texture Map is cleaned!" << std::endl;
}

