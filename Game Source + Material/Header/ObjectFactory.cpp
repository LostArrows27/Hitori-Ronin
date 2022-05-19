#include "ObjectFactory.h"
#include "Enemy.h"
#include "Warrior.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType(std::string className, std::function<ObjectPtr(Transform* tf)> type){
    m_TypeRegistry[className] = type;
}
//

ObjectPtr ObjectFactory::CreateObject(std::string type, Transform* tf){

    ObjectPtr object = nullptr;
    auto it = m_TypeRegistry.find(type); // using the find function in map
    if(it != m_TypeRegistry.end())
        object = it->second(tf);

    return object;
    // search all the "Registrat"
    // Ta da dang ky all registart trong cac class
    // so yeah we can simply find the class we want to create
}
