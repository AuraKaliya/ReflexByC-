#pragma once
#include "Factory.hpp"

template <class Base, typename... Args>
class Register
{
public:
    Register(const std::string& objectName, std::function<Base* (Args...)> objectClass,const std::string& objectTypeIdName)
    {
        Factory<Base, Args...>* factory = Factory<Base, Args...>::GetInstance();
        factory->RegisterClass(objectName, objectClass);
        factory->RegisterClass(objectName,objectTypeIdName);

    }
    Register(const std::string& objectName,std::function<Base*(Base&)> objectCopyClass)
    {
        Factory<Base, Args...>* factory = Factory<Base, Args...>::GetInstance();
        factory->RegisterClass(objectName,objectCopyClass);
    }
};
//createFactoryCopyCreator < objectClass , baseClass > ( )


#define REGISTER_FUNCTIONNAME(line,objectClass,baseClass) Register_##objectClass##_##line

#define REGISTER_CLASS_ARGS(line, objectClass ,baseClass,...) \
   static Register< baseClass , ##__VA_ARGS__ > REGISTER_FUNCTIONNAME( line,objectClass,baseClass)\
(  \
#objectClass  , createFactoryCreator < objectClass , baseClass , ##__VA_ARGS__ > ( ) , typeid(objectClass).name( )  \
);

#define REGISTER_CLASS( objectClass , baseClass , ... ) REGISTER_CLASS_ARGS( __LINE__,  objectClass ,baseClass , ##__VA_ARGS__ )

#define REGISTER_COPY_FUNCTIONNAME(line,objectClass,baseClass) Register_Copy_##objectClass##_##line

#define REGISTER_COPY_CLASS_ARGS(line, objectClass ,baseClass,...) \
   static Register< baseClass , ##__VA_ARGS__ > REGISTER_COPY_FUNCTIONNAME( line , objectClass ,baseClass )(  \
#objectClass  , createFactoryCopyCreator < objectClass , baseClass > ( ) );

#define REGISTER_COPY_CLASS(objectClass,baseClass , ... ) REGISTER_COPY_CLASS_ARGS( __LINE__ , objectClass ,baseClass , ##__VA_ARGS__ )
