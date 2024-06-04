#pragma once
#include "Factory_C17.hpp"

class Register
{
public:
    template <class Base, typename... Args>
    Register(const std::string& objectName,  const std::string& objectTypeIdName, std::function<Base* (Args...)> objectClass, std::function<Base* (Base&)> objectCopyClass)
    {
        Factory<Base, Args...>* factory = Factory<Base, Args...>::GetInstance();
        factory->RegisterClass(objectName, objectClass);
        factory->RegisterClass(objectName,objectTypeIdName);

        Factory<Base>* baseFactory = Factory<Base>::GetInstance();
        baseFactory->RegisterClass(objectName, objectCopyClass);
    }
};

#define REGISTER_FUNCTIONNAME(line,objectClass,baseClass) Register_##objectClass##_##line

#define REGISTER_CLASS( objectClass , baseClass , ... ) REGISTER_CLASS_ARGS( __LINE__,  objectClass ,baseClass , ##__VA_ARGS__ )

#define REGISTER_CLASS_ARGS(line,objectClass , baseClass , ... )  \
static Register REGISTER_FUNCTIONNAME(line,objectClass){ #objectClass ,typeid(objectClass).name(),\
std::function < baseClass * ( __VA_ARGS__ )> { [](auto &&... args)->decltype(auto)\
{\
    return new objectClass{args...};\
}},\
std::function < baseClass * (baseClass & )> { []( baseClass & other)->baseClass * \
{\
    return new objectClass(* static_cast<objectClass *> ( &other ));\
}}\
};