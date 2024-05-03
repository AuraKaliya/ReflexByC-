#pragma once
#include "Factory.hpp"

template <class Base, typename... Args>
class Register
{
public:
    Register(const std::string& objectName, std::function<Base* (Args...)> objectClass)
    {
        Factory<Base, Args...>* factory = Factory<Base, Args...>::GetInstance();
        factory->RegisterClass(objectName, objectClass);
    }
};

#define REGISTER_FUNCTIONNAME(line,objectClass,baseClass) Register_##objectClass##_##line
#define REGISTER_CLASS_ARGS(line,objectClass,baseClass,...) \
   static Register< baseClass , ##__VA_ARGS__ > REGISTER_FUNCTIONNAME(line,objectClass,baseClass)(  \
#objectClass  , createFactoryCreator < objectClass , baseClass , ##__VA_ARGS__ > ( ) );
#define REGISTER_CLASS(objectClass,baseClass,...) REGISTER_CLASS_ARGS(__LINE__,objectClass,baseClass,##__VA_ARGS__)