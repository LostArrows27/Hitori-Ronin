#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include <vector>
#include "TileMap.h"
#include "tinyxml.h"
#include "GameObject.h"
#include "TileLayer.h"
#include "ObjectFactory.h"

class Parser {

   public:
        bool ParseTextures(std::string source);
        TileMap* ParseMap(std::string source);
        void ParseGameObjects(std::string source, ObjectList* target);
        inline static Parser* Instance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new Parser();}

    private:
        Parser(){}
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

    private:
        static Parser* s_Instance;
};

#endif // MAPPARSER_H