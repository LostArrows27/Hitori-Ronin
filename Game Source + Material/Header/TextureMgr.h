#ifndef TEXTUREMGR_H
#define TEXTUREMGR_H

#include "Transform.h"
#include <string>
#include "SDL.h"
#include <map>

using TextureMap = std::map<std::string, SDL_Texture*>;

class TextureMgr {

    public:
        void Clean();
        SDL_Texture* Load(std::string filename);
        bool Add(std::string id, std::string filename);
        void QueryTexture(std::string id, int* out_w, int* out_h);

        void Draw(Transform* tf);
        void DrawFrame(Transform* tf, int row, int frame);
        void DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio=1.0f);

        inline TextureMap GetTextureMap(){return m_TextureMap;}
        inline SDL_Texture* GetTexture(std::string id){return m_TextureMap[id];}
        inline static TextureMgr* Instance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureMgr();}

    private:
        TextureMgr(){}
        TextureMap m_TextureMap;
        static TextureMgr* s_Instance;
};

#endif // TEXTUREMANAGER_H