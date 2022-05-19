#include "Parser.h"
#include "SoundMgr.h"
#include "TextureMgr.h"

Parser* Parser::s_Instance = nullptr;

bool Parser::ParseSounds(std::string source){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }
    // root: "sound"
    // child element: "effect" and "music"
    TiXmlElement* root = xml.RootElement(); //lay thong tin tu file xml theo duong dan ta truyen vao
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){

        if(e->Value() == std::string("effect")){
            SoundMgr::Instance()->LoadEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }

        if(e->Value() == std::string("music")){
            SoundMgr::Instance()->LoadMusik(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
    // we will "tan dung" the "tml" file and load all our sound instead of write a bunch of code to load it here
}

bool Parser::ParseTextures(std::string source){
    //basically, we create an "xml" file that all contain our game
    // texture id, each id have its own "folder source"
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement(); // the "<texture>" one
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("texture")){
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            TextureMgr::Instance()->Add(id, source);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

TileMap* Parser::ParseMap(std::string source){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load: " << source << std::endl;
        return nullptr;
    }

    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    TilesetsList tilesets;
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    TileMap* gamemap = new TileMap();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return gamemap;
}

bool Parser::ParseGameObjects(std::string source, ObjectList* target){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout << "Failed to load: " << source << " " << xml.ErrorDesc() << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement(); // the root = <object>

    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("object")){

            int x, y, width, height, flip = 0;
            double scX, scY, sratio, rot = 0.0f;

            std::string objType = e->Attribute("type");
            std::string texID = e->Attribute("texture");

            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("w", &width);
            e->Attribute("h", &height);

            e->Attribute("flip", &flip);
            // flip = 0 -> non flip
            // flip = 1 -> flip horizontally
            // flip = 2 > flip verticaly
            e->Attribute("scX", &scX); // ti le cua chieu cao va chieu rong se x scX, scY
            e->Attribute("scY", &scY);

            e->Attribute("sratio", &sratio); // how fast the object move when camera moving
            e->Attribute("rot", &rot); // rot is the rotation angle of the texture
            // quay theo chieu kim dong ho

            Transform* tfr = new Transform(x, y, width, height, texID, (SDL_RendererFlip)flip, scX, scY, rot, sratio);
            // after taking all information in the file, we create a new Tf data for our object
            ObjectPtr object = ObjectFactory::Instance()->CreateObject(objType, tfr);

            if(object != nullptr)
                target->push_back(object);
            // then parse all the object we find to the list then render
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

Tileset Parser::ParseTileset(TiXmlElement* xmlTileset){
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);
    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
    // 1st tileset will begin with first id = 1 and lastid = tilecount - 1
    // since we have many tileset so it's important to "+" first id
    // -------------------------------
    // this function was like ( A, &B)
    // u take data of A and pass it to B by "&"
    xmlTileset->Attribute("columns", &tileset.Width);
    tileset.Height = tileset.TileCount/tileset.Width;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    // file string of the tile source
    return tileset;
}

TileLayer* Parser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetsList tilesets, int tilesize, int rowcount, int colcount){
    // every xml file have many 2D matrix
    // and each 1 is a matrix of each layer in your map
    TiXmlElement* data;
    for(TiXmlElement* e=xmlLayer->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("data")){
            data = e;
            break;
        }
    }
    // seach all the <...> component till you find "data"
    // cause we have the Parse tile set function over there
    // and the vector <tileset> which is tileset list so that list
    // contain all tileset information

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMatrix tilemap(rowcount, std::vector<int> (colcount, 0));
    for(int row = 0; row < rowcount; row++){
        for (int col = 0; col < colcount; col++){
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];
            // take a string "number" and parse it into tilemap which is a <vector> int
            if(!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}


