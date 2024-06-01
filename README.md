# Reflex_cpp

A set of general-purpose C++ templates that implement precompile-time reflection.

* 2024.6.1 ：add Copy Constructor Creator, need base-class's copy constructor.



# Example

* Step1: Edit Base Class

```c++
//.h
#pragma once
class ObjectBase
{
public: 
	explicit ObjectBase();
	explicit ObjectBase(int  index);
	virtual ~ObjectBase() = default;
	virtual void work() = 0;
	int GetIndex();
protected:
	int m_index;
};

//.cpp
#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
	m_index = -1;
}

ObjectBase::ObjectBase(int index):m_index(index)
{

}

int ObjectBase::GetIndex()
{
	return m_index;
}
```

* Step2: Edit Concrete Class

```c++
//.h
#pragma once
#include "ObjectBase.h"
#include "Registor.hpp"

class ObjectA :
    public ObjectBase
{
public:
	explicit ObjectA();
	explicit ObjectA(int  index);
	void work()override;
};

REGISTER_CLASS(ObjectA,ObjectBase,int)
REGISTER_CLASS(ObjectA,ObjectBase)

//.cpp
#include "ObjectA.h"
#include <iostream>

ObjectA::ObjectA():ObjectBase()
{
}

ObjectA::ObjectA(int index):ObjectBase(index)
{

}

void ObjectA::work()
{
	std::cout << "Now ObjectA work." << std::endl;
}
```

* Step3: Using in Main

```c++
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "ObjectBase.h"
using namespace std;
int main()
{
	ObjectBase* obj_1 = Factory<ObjectBase, int>::GetInstance()->CreateClass("ObjectA",8);
	obj_1->work();
	int res = obj_1->GetIndex();
	cout << " Res1:" << res << endl;

	ObjectBase* obj_2 = Factory<ObjectBase>::GetInstance()->CreateClass("ObjectA");
	obj_2->work();
	res = obj_2->GetIndex();
	cout << " Res:" << res << endl;
	return 0;
}

```

