#ifndef TILELAYER_H
#define TILELAYER_H

#include <SDL.h>
#include <vector>
#include "Camera.h"
#include "TextureMgr.h"



struct Tileset{
    int FirstID, LastID;
    // cause actually the map is only text file
    // so every image has its own ID
    // firstID = "firstgid"
    int Height, Width;
    int TileCount, TileSize;
    // "tileimage" have how many tile in it
    std::string Name, Source;
    // name is the "name" in TMX app that you named it:D
};

using TilesetsList = std::vector<Tileset>;
using TileMatrix = std::vector<std::vector<int> >;

// basicly the map.tmx file will contain all tileset image that we use
// every tileset image we use will be like a 2D matrix with number
// so we need a 2D vector to store that
// -------
// in a map, "0" mean its have no tileset

class TileLayer {

    public:
        TileLayer(int tilesize, int width, int rowcount, TileMatrix tilemap, TilesetsList tilesets):
        m_TileSize(tilesize), m_Width(width), m_Height(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets){}

        void Render(){
            for(unsigned int i = 0; i < m_Height; i++){
                for(unsigned int j = 0; j < m_Width; j++){

                    int tileID = m_Tilemap[i][j];
                    int temp = tileID;

                    if(tileID == 0){continue;} // there's no tile at map so we continue loop
                    else {
                        int ts_index = 0;
                        if(m_Tilesets.size() > 1){
                            for(unsigned int k = 1; k < m_Tilesets.size(); k++){
                                if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID){
                                    tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                                    ts_index = k;
                                    break;
                                }
                            }
                        }
                        // well as i said that 1st tile will have id 1 and last id = tilecount
                        // 2nd first_tile will be last of 1 + 1
                        // and there so on when we have a tileID number
                        // we have to check if it was in range of the "Tileset" that we need to check

                        Tileset ts = m_Tilesets[ts_index];
                        int tileRow = tileID/ts.Width;
                        int tileCol = tileID - tileRow*ts.Width-1;
                        // after you take the tileID and know which tileset it was in
                        // you define the pos of it in the tileset by the 2 following "phep tinh"

                        // if this tile is on the las column
                        if(tileID % ts.Width == 0){
                            tileRow--;
                            tileCol = ts.Width - 1;
                        }

                        TextureMgr::Instance()->DrawTile(ts.Name, j*m_TileSize, i*m_TileSize, m_TileSize, tileRow, tileCol);
                        // u can adjust the 3rd and 4th element of this drawtile function
                        // to adjust the start point of the map.
                        // i add +65 to the 4th element, which is the y axis, so that the map can fall down a bit compare to the first map
                    }
                }
            }
        }

        void Update(){}
        inline int GetTileSize(){return m_TileSize;}
        inline int GetWidth(){return m_Width*m_TileSize;}
        inline int GetHeight(){return m_Height*m_TileSize;}
        inline TileMatrix GetTileMap(){return m_Tilemap;}

    private:
        TileMatrix m_Tilemap;
        TilesetsList m_Tilesets;
        int m_TileSize, m_Width, m_Height;
};

#endif // TILELAYER_H
