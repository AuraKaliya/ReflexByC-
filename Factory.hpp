#pragma once
#include <string>
#include <map>
#include <functional>

template <class T, typename... Args>
class Factory
{
public:
    static Factory<T, Args...>* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Factory();
        }
        return m_instance;
    }

    void RegisterClass(const std::string& objectName, std::function< T* ( Args... ) > objectClass)
    {
        m_factoryCreator[objectName] = objectClass;
    }

    void RegisterClass(const std::string& objectName, const std::string& typeIdName)
    {
        m_factoryTypeIdDictionary[objectName] = typeIdName;
    }

    void RegisterClass(const std::string& objectName, std::function<T* (T&)> objectCopyClass )
    {
        m_factoryCopyCreator[objectName]=objectCopyClass;
    }

    T* CreateClass(const std::string& objectName, Args... args)
    {
        auto it = m_factoryCreator.find(objectName);
        if (it != m_factoryCreator.end())
        {
            return it->second(args...);
        }
        else
        {
            return nullptr;
        }
    }
    T* CreateClassByCopy(const std::string& objectName, T& obj)
    {
        auto it = m_factoryCopyCreator.find(objectName);
        if (it != m_factoryCopyCreator.end())
        {
            return it->second(obj);
        }
        else
        {
            return nullptr;
        }
    }
    std::string getClassTypeIdName(const std::string& objectName)
    {
        return m_factoryTypeIdDictionary[objectName];
    }

private:
    static Factory<T, Args...>* m_instance;

    Factory() = default;

    std::map<std::string, std::function<T* (Args...) > > m_factoryCreator;
    std::map<std::string,std::function<T* (T&)> > m_factoryCopyCreator;
    std::map<std::string, std::string > m_factoryTypeIdDictionary;
};

template <class T, class... Args>
Factory<T, Args...>* Factory<T, Args...>::m_instance = nullptr;

template <class T, class Base, class... Args>
std::function<Base* (Args...)> createFactoryCreator()
{
    return [](Args... arg) ->Base*
    {
        return new T(arg...);
    };
}

template <class T , class Base>
std::function<Base* (Base&)> createFactoryCopyCreator()
{
    return [](Base& other) ->Base*
    {
        return new T(* static_cast<T*>(&other) );
    };
}
