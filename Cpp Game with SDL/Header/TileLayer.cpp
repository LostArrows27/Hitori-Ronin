#include "TileLayer.h"
#include "TextureManager.h"

//#include<iostream>

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetsList tilesets) :
m_TileSize (tilesize), m_ColCount (colcount), m_RowCount(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets){
    for(unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstace()->Load(m_Tilesets[i].Name, "Map/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    for(unsigned int i = 0; i < m_RowCount; i++)
    {
        for(unsigned int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_Tilemap[i][j];
            if(tileID == 0)
                continue;
            else
            {
                int index = 0; // checking what tile set are we using
                if(m_Tilesets.size() > 1) // > 1 tile set
                {
                    for(unsigned int k = 1; k < m_Tilesets.size(); k++)
                    {
                        if(tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }
                Tileset ts = m_Tilesets[index];
                int tileRow = tileID/ts.ColCount;
                int tileCol = tileID - tileRow*ts.ColCount-1;

                if(tileID % ts.ColCount == 0)
                {
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }
                //std::cout << "[" << j << "][" << i << "] : ";
                TextureManager::GetInstace()->DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tileRow, tileCol);
                // u can adjust the 3rd and 4th element of this drawtile function
                // to adjust the start point of the map.
                // i add +65 to the 4th element, which is the y axis, so that the map can fall down a bit compare to the first map
            }
        }
    }
}

void TileLayer::Update()
{

}



