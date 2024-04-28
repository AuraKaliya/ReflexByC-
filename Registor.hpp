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

#define REGISTER_CLASS(objectClass,baseName,...) \
static Register< baseName , ##__VA_ARGS__ > Register_##objectClass_##__VA_ARGS__(  \
#objectClass  , createFactoryCreator < objectClass , baseName , ##__VA_ARGS__ > ( ) );