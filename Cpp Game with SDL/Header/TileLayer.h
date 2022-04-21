#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

// trong 1 map thi 0 la khong co tileset
// id cua tileset la so, xem trong phan mem tilemap

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount; // cot va hang cua tileset ta lay chia theo kich thuoc 1 tileset
    int TileCount, TileSize;
    std::string Name, Source; // Name is tileset's name
};

using TilesetsList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
    public:
        TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetsList tilesets);
        virtual void Render();
        virtual void Update();
        inline TileMap GetTilemap() {return m_Tilemap;}


    private:
        int m_TileSize;
        int m_RowCount, m_ColCount;

        TileMap m_Tilemap;
        TilesetsList m_Tilesets;
};



#endif // TILELAYER_H
