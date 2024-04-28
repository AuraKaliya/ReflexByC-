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

private:
    static Factory<T, Args...>* m_instance;

    Factory() = default;

    std::map<std::string, std::function<T* (Args...) > > m_factoryCreator;
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