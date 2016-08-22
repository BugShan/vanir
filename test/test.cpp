#include "test.h"
#include <iostream>
#include <vanir/Vanir.h>
#include <vanir/Type.h>
#include <vanir/Class.h>
#include <vanir/Field.h>
#include <vanir/Method.h>

using namespace vanir;

IMPORT_MODULE(Test);

namespace test
{
	void Base1::foo1(const int i)
	{
		std::cout << "Base1::foo1: " << i << std::endl;
	}

	void Base2::foo2(const float f)
	{
		std::cout << "Base2::foo2: " << f << std::endl;
	}

	void Test::foo2(const float f)
	{
		std::cout << "Test::foo2: " << f << std::endl;
	}
};//namespace test


int main(void)
{
	vanir::InitVanir();
	vanir::LoadModule(TestModule::GetMe());

	std::cout << "Vanir Test" << std::endl;
	const auto& type_list = vanir::GetAllTypeList();
	for(const auto typePtr : type_list)
	{
		std::cout << typePtr->GetFullName() << std::endl;
		if(typePtr->IsClass())
		{
			const Class* classPtr = static_cast<const Class*>(typePtr);
			for(auto fieldPtr : classPtr->GetFieldPtrVec())
				std::cout << fieldPtr->GetName() << std::endl;
			for(auto methodPtr : classPtr->GetMethodPtrVec())
				std::cout << methodPtr->GetName() << std::endl;
		}
	}
	return 0;
}
