#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Transform.h"
#include "GameObject.h"

class ObjectFactory{

    public:
        ~ObjectFactory(){m_TypeRegistry.clear();}
        ObjectPtr CreateObject(std::string type, Transform* tf);
        void RegisterType(std::string className, std::function<ObjectPtr(Transform* tf)> type);
        static ObjectFactory* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new ObjectFactory();}
        // you want your game to create object 1 times so that saving your com memory
    private:
        ObjectFactory(){}
        static ObjectFactory* s_Instance;
        std::map<std::string, std::function<ObjectPtr(Transform* tf)>> m_TypeRegistry;

};

template<class Type>
class Registrar {

    public:
        Registrar(std::string className){
            ObjectFactory::Instance()->RegisterType(className,
            [](Transform* tf)->ObjectPtr{
                return new Type(tf);
                //return std::unique_ptr<Type>(new Type(tf));
            });
        }
};
// it was like
// if Type = "PLAYER" --> return new Player()
// if Type = "ENEMY" --> return new Enemy()

#endif // GAMEOBJECTFACTORY_H

