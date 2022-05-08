#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int width, int rowcount, TileMatrix tilemap, TilesetsList tilesets):
m_TileSize(tilesize), m_Width(width), m_Height(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets){}

void TileLayer::Render(){
    for(unsigned int i = 0; i < m_Height; i++){
        for(unsigned int j = 0; j < m_Width; j++){

            int tileID = m_Tilemap[i][j];
            int temp = tileID;

            if(tileID == 0)
                continue;

            else{
                int index = 0;
                if(m_Tilesets.size() > 1){
                    for(unsigned int k = 1; k < m_Tilesets.size(); k++){
                        if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID){
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                Tileset ts = m_Tilesets[index];
                int tileRow = tileID/ts.Width;
                int tileCol = tileID - tileRow*ts.Width-1;

                // if this tile is on the las column
                if(tileID % ts.Width == 0){
                    tileRow--;
                    tileCol = ts.Width - 1;
                }

                TextureManager::GetInstance()->DrawTile(ts.Name, j*ts.TileSize, i*ts.TileSize, ts.TileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update(){}

