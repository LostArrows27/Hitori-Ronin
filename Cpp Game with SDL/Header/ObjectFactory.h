#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <map>
#include <string>
#include <memory>
#include "GameObject.h"
#include <functional>

// this class for creating small object ingame like car, moving tree, ....

class ObjectFactory {

    public:
        GameObject* CreateObject(std::string type, Properties* props); // type of the object or its name
        void RegisterType(std::string className, std::function<GameObject*(Properties* props)> type);
        static ObjectFactory* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new ObjectFactory();}

    private:
        ObjectFactory(){}
        static ObjectFactory* s_Instance;
        std::map<std::string, std::function<GameObject*(Properties* props)>> m_TypeRegistry;
};

template<class Type>
class Registrar {

    public:
        Registrar(std::string className){
            ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
        }
};

#endif // GAMEOBJECTFACTORY_H

