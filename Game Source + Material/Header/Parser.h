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

// this class will parse all game source like map.tmx file, character.tml file
// it's take a string source and parse to my game

class Parser {

   public:
        TileMap* ParseMap(std::string source);
        bool ParseSounds(std::string source);
        bool ParseTextures(std::string source);
        bool ParseGameObjects(std::string source, ObjectList* target);

        // this function to parse gameobject
        // this is the main function that our character will use
        inline static Parser* Instance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new Parser();}

    private:
        Parser(){}
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        // parse all information of tmx file with <tileset> is the mother component
        // it will contain "firstgid", "tilewidth" ,....
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

    private:
        static Parser* s_Instance;
};

#endif // MAPPARSER_H
